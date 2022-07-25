import os, sys
from optparse import OptionParser

activities = {}
massdict = {'DetectorBody':26.743101,
           'LIMEinternalStructure':8.1656306,
           'CameraBody':2.1675000,
           'CameraLens':0.19499790,
           'LIMEendPMT':0.11166214,
           'GEMstretchers':0.061524439,
           'GEMsupportStructure':0.92605176,
           'GEMfoils':0.039264506,
           'Cathode':1.6498523,
           'FieldRings':11.826861,
           'LIMEResistors':0.054339129,
           'CopperShielding10cm':4508.8901}

def query_yes_no():
    yes = set(['yes','y'])
    no = set(['no','n'])

    choice = input()
    if choice in yes:
        return True
    elif choice in no:
        return False
    else:
        print ('Please respond with yes or no')
        query_yes_no()

def parseInputArgs():
    parser = OptionParser()

    parser.add_option('-i', '--input', default=None, help='Input file with list of activities for each isotope')
    parser.add_option('-c', '--cuts', default='0', help='No cuts by default. Otherwise string with cuts to be applied to x_hits[0], y_hits[0] and z_hits[0]')
    parser.add_option('-t', '--tag', default='tag', help='Tag to identify the simulation (e.g. LIME_CADshield_10Cu)')
    parser.add_option('-o', '--simout', default='/jupyter-workspace/cloud-storage/cygno-sim/LIME_MC_data/', help='directory containing GEANT4 output files to be analysed')
    
    (options, args) = parser.parse_args()
    return options

def readInput(filepath):
    
    file = open(filepath)
    
    for line in file:
        line.strip()
        elements = line.split()
        if len(elements)==0 or line[0]=='#': continue
        if not 'part' in activities: activities['part'] = elements[0]
        activities[elements[1]] = float(elements[2])
    print(activities)
      

def WriteLists():
    
    options = parseInputArgs()
    
    if os.path.exists('lists/%s'%(options.tag)):
        print('%s already exists. Do you want to write the lists there? (y/n)'%('lists/%s'%(options.tag)))
        if not query_yes_no():
            print('Specify another tag')
            sys.exit()
    else: 
        print('Creating new folder lists/%s'%(options.tag))
        listpath = 'lists/%s'%(options.tag)
        os.system("mkdir -p %s/"%(listpath))
        for key in activities:
            if not key=='part':
                filename=listpath+'/list_{tag}_{part}_{isotope}'.format(tag=options.tag, part=activities['part'], isotope=key)
                #file = open(filename)
                os.system('find {outpath} -name "{isotope}*.root" > {listfile}'.format(outpath=options.simout, isotope=key, listfile=filename))
        
    if os.path.exists('output/%s'%(options.tag)):
        print('%s already exists. Do you want to write the output root files there? (y/n)'%('output/%s'%(options.tag)))
        if not query_yes_no():
            print('Specify another tag')
            sys.exit()
    else: 
        print('Creating new folder output/%s'%(options.tag))
        output = 'output/%s'%(options.tag)
        os.system("mkdir -p %s/"%(output))
        
    if os.path.exists('config/%s'%(options.tag)):
        print('%s already exists. Do you want to write the config files there? (y/n)'%('config/%s'%(options.tag)))
        if not query_yes_no():
            print('Specify another tag')
            sys.exit()
    else: 
        print('Creating new folder config/%s'%(options.tag))
        config = 'config/%s'%(options.tag)
        os.system("mkdir -p %s/"%(config))
        
        
def WriteConfig():
    
    options = parseInputArgs()
    
    for key in activities:
        if not key=='part': 
            file = open('config/{tag}/conf_{tag}_{part}_{isotope}'.format(tag=options.tag, part=activities['part'], isotope=key),'w')
            file.write('externalflux 0\n')
            file.write('CYGNO_gas_mass 0.068732424\n')
            file.write('LIMEShield 1\n')
            file.write('FromShield -1\n')
            file.write('smearing 0\n')
            file.write('mass {mass}\n'.format(mass=massdict[activities['part']]))
            file.write('activity {act}\n'.format(act=activities[key]))
            if options.cuts=='0': file.write('ApplyCuts 0\n')
            else: 
                file.write('ApplyCuts 1\n')
                file.write('Cuts {cut}\n'.format(cut=options.cuts))
            file.write('filelist {lists}\n'.format(lists='lists/'+options.tag+'/list_{tag}_{part}_{isotope}'.format(tag=options.tag, part=activities['part'], isotope=key)))
            file.write('root_out output/{tag}/{tag}_{part}_{isotope}.root'.format(tag=options.tag, part=activities['part'], isotope=key))
            file.close()
            
            
options = parseInputArgs()
readInput(options.input)
WriteLists()
WriteConfig()
print('Done. Do you want to run the analysis? (y/n)')
if not query_yes_no():
    sys.exit()
else: 
    configpath = 'config/%s'%(options.tag)
    outputpath = 'output/%s'%(options.tag)
    for config in os.listdir(configpath):
        if config.startswith('conf'): os.system('./CYGNOAnalysis {cpath}/{conf} > {opath}/{oname}.out'.format(cpath=configpath, conf=config, opath=outputpath, oname=config.split('/')[-1][5:]))
        #if config.startswith('conf'): print('./CYGNOAnalysis {cpath}/{conf} > {opath}/{oname}.out'.format(cpath=configpath, conf=config, opath=outputpath, oname=config.split('/')[-1][5:]))