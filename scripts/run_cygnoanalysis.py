import os

def RunAnalysis(tag):
    configpath = 'config/%s'%(tag)
    outputpath = 'output/%s'%(tag)
    for config in os.listdir(configpath):
        if config.startswith('conf'): os.system('./CYGNOAnalysis {cpath}/{conf} > {opath}/{oname}.out'.format(cpath=configpath, conf=config, opath=outputpath, oname=config.split('/')[-1][5:]))
        
RunAnalysis('LIME_CADshield_6Cu_neutrons')