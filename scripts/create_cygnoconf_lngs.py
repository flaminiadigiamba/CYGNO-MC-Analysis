#! /usr/bin/env python
import os
import sys
import argparse
import re
from ROOT import *
import glob
import subprocess
import getpass

usage = "usage : ..."
print usage
parser = argparse.ArgumentParser(description='Process options.')
#parser.add_argument("--volume", type=str, dest="volume", default="",
#    help="Volume name",
#    )
#parser.add_argument("--activity", type=float, dest="activity", default=1.,
#    help="Activity in Bq/kg",
#    )
#parser.add_argument("--isotope", type=str, dest="isotope", default="K40",
#    help="Isotope",
#    )
#parser.add_argument("--smearing", type=store_true, dest="smearing", default=True,
#    help="Apply resolution smearing to the spectrum if this option is used",
#    )
parser.add_argument("-i", type=str, dest="inputconf", default=None,
    help="Text file containing a table with following structure:  ## Volume_name    Isotope    Activity[Bq/kg]    Smearing[0 or 1] ",
    )
parser.add_argument("--workdir", type=str, dest="workdir", default="/ua9/user/dimperig/CYGNO/CYGNO-MC-Analysis",
    help="output dir for rootfile with histograms and summary Tree",
    )
parser.add_argument("--tag", type=str, dest="tag", default="",
    help="Output directory name",
    )
parser.add_argument("--list",type=str, dest="listdir", default="",
    help="list directory name"
)
parser.add_argument("--split",type=int, dest="maxfilesperjob", default=-999,
    help="maximum files per job, only for externals"
)
parser.add_argument("--external",action="store_true", dest="external", default=False,
    help="maximum files per job"
)
parser.add_argument('-r', '--retry', default=False, action='store_true',
    help='It looks in the output folder and watch for missing files and resubmit them.'
)
parser.add_argument('--lime', default=False, action='store_true', dest="lime",
    help='Bool to indicate if you are analyzing lime geometry.'
)

args = parser.parse_args()
print args 

os.system("mkdir -p logs/"+args.tag)
os.system("mkdir -p submit/"+args.tag)
os.system("mkdir -p output/"+args.tag)
os.system("mkdir -p config/"+args.tag)

if not (args.lime):
  mass = {
  "foo":-999,
  "Shield0":86539.5,
  "Shield1":16113.5,
  "Shield2":57782.8,
  "Shield3":8738.24,
  "AcrylicBox":201.072,
  "cad_camera_carter_physical":14.0275,
  "cad_cameras_all_physical":32.7229,
  "cad_fc_support_physical":29.77,
  "cad_turns_support_physical":34.7248,
  "cad_field_cage_physical":42.4915,
  "cad_gem_support_physical":15.7757,
  "cad_gem_physical":0.4684,
  "cad_cathode_frame_physical":56.5125,
  "cad_cathode_physical":0.98408,
  "TPC_gas":2*0.98408,
  "CYGNO_gas":2*0.810438,
  "CameraBody":18*2.1275,  
  }

else:
  mass = {
  "foo":-999,
  "TPC_gas":0.14796409,
  "CYGNO_gas":0.068732424,
  "CameraBody":2.1675,
  "CameraLens":0.194998,

}


splittedlists = []

#nlists = 0
#for l in os.listdir("lists/"+args.listdir):
#  nlists +=1
nlists = len(glob.glob1("lists/"+args.listdir,"*.txt"))

#print nlists
#print args.maxfilesperjob

if (nlists==1 and args.maxfilesperjob>0):  
  jf=0  ##counter for num of files
  jj=0  ##counter for num of jobs
  file_inputList = open("lists/"+args.listdir+"/"+os.listdir("lists/"+args.listdir)[0],"r") 
  nfiles = 0
  os.system("mkdir -p lists/"+args.listdir+"/split" )
  os.system("rm -f lists/"+args.listdir+"/split/*" )
  for line in file_inputList:
      modulo = int(jf+1) % int(args.maxfilesperjob)
      #print "file:%i  filesperjob:%i  job:%i op.modulo:%i  list %s " % (jf, args.maxfilesperjob,jj,modulo, line)
      splittedlistfilename = "lists/"+args.listdir+"/split/list_external_"+args.tag+"_part_"+str(jj)+".list"
      splittedlist = open(splittedlistfilename,"a+")
      splittedlist.write(line)
      if ( modulo == 0 or jf+1==nfiles ):
          splittedlist.close()
          splittedlists.append(splittedlist)
          jj+=1
      jf+=1
  nfiles = jf+1

#print nfiles

njobs = len(splittedlists)
ijob=0
print("n jobs = %s"%njobs)
inputconf = open(args.inputconf,"r")
templateconflist = []
templatesubmitlist = []

if args.lime:
  detmass = 0.068732424
else:
  detmass = 2*0.810438 


for line in inputconf:
  template_conf_decay =  """externalflux 0
CYGNO_gas_mass"""+ str(detmass) +"""
mass MASS
activity ACTIVITY
half_life HALFLIFE 
smearing SMEARING
filelist lists/LISTDIR/list_ISOTOPE_RadioactiveDecayFromVOLUME.txt
root_out OUTPUTFILE_DECAY"""
  submit_template_decay = """#!/bin/bash
#PBS -j oe  
#source /storage/local/exp_soft/cygnorm3/root-v6-12-06-install/bin/thisroot.sh 
newgrp cygno << END
echo This is running as group \$(id -gn)
END
source /nfs/cygno/software/root-v6-18-04-install/bin/thisroot.sh
cd WORKDIR
pwd
time ./CYGNOAnalysis config/"""+args.tag+"""/cygnoconf_ISOTOPE_RadioactiveDecayFromVOLUME  > logs/"""+args.tag+"""/Analysis_log_ISOTOPE_RadioactiveDecayFromVOLUME"""+"""\n"""

  if (args.maxfilesperjob)<0:
    template_conf_externals =  """externalflux 1
CYGNO_gas_mass """+ str(detmass) +"""
externalflux_value FLUX
shield0_thickness THICK0
shield1_thickness THICK1 
shield2_thickness THICK2 
shield3_thickness THICK3 
smearing SMEARING
filelist lists/LISTDIR/list_external_SHIELDGEO.txt
root_out OUTPUTFILE_EXT\n"""
  
    submit_template_externals = """#!/bin/bash
#PBS -j oe  
#source /storage/local/exp_soft/cygnorm3/root-v6-12-06-install/bin/thisroot.sh
newgrp cygno << END
echo This is running as group \$(id -gn)
END
source /nfs/cygno/software/root-v6-18-04-install/bin/thisroot.sh
cd WORKDIR
pwd
time ./CYGNOAnalysis config/"""+args.tag+"""/cygnoconf_external_"""+args.tag+""" > logs/"""+args.tag+"""/Analysis_log_external_"""+args.tag+"""\n"""

  else:
    for ijob in range(0,njobs):
      template_conf_externals =  """externalflux 1
externalflux_value FLUX
CYGNO_gas_mass """+ str(detmass) +"""
shield0_thickness THICK0
shield1_thickness THICK1 
shield2_thickness THICK2 
shield3_thickness THICK3 
smearing SMEARING
filelist """+splittedlists[ijob].name+"""
root_out OUTPUTFILE_EXT_PART\n"""
      templateconflist.append(template_conf_externals)
      submit_template_externals = """#!/bin/bash
#PBS -j oe  
#source /storage/local/exp_soft/cygnorm3/root-v6-12-06-install/bin/thisroot.sh 
newgrp cygno << END
echo This is running as group \$(id -gn)
END
source /nfs/cygno/software/root-v6-18-04-install/bin/thisroot.sh
cd WORKDIR
pwd
time ./CYGNOAnalysis config/"""+args.tag+"""/cygnoconf_external_"""+args.tag+"""_part_"""+str(ijob)+""" > logs/"""+args.tag+"""/Analysis_log_external_"""+args.tag+"""_part_"""+str(ijob)+"""\n"""
      templatesubmitlist.append(submit_template_externals)
 
  vol_name="foo"
  isotope = "foo"
  activity = -999  
  halflife = -999
  flux = -999
  thick0 = -999
  thick1 = -999
  thick2 = -999
  thick3 = -999
  smearing = 0

  if not args.external and not line.startswith("#"):
    vol_name = line.split()[0]
    isotope = line.split()[1]
    activity = line.split()[2]
    smearing = line.split()[3]
    halflife = line.split()[4]
  elif args.external and not line.startswith("#"): 
    print line
    flux = line.split()[0]
    thick0 = line.split()[1]
    thick1 = line.split()[2]
    thick2 = line.split()[3]
    thick3 = line.split()[4]
    smearing = line.split()[5]
    
  if not line.startswith("#"):
    dict_replace_external = {
        "THICK0":thick0,
        "THICK1":thick1,
        "THICK2":thick2,
        "THICK3":thick3,
        "WORKDIR":args.workdir,
        "LISTDIR":args.listdir,
        "SMEARING":smearing,
        "SHIELDGEO":args.tag,
        "FLUX":flux,
        "OUTPUTFILE_EXT":"%s/output/%s/out_external_%s.root"%(args.workdir,args.tag,args.tag),
        "OUTPUTFILE_EXT_PART":"%s/output/%s/out_external_%s_part_IJOB.root"%(args.workdir,args.tag,args.tag)
        }
    
    
    dict_replace = {
        "WORKDIR":args.workdir,
        "LISTDIR":args.listdir,
        "VOLUME":vol_name,
        "MASS":str(mass[vol_name]),
        "ACTIVITY":activity,
        "HALFLIFE":halflife,
        "ISOTOPE":isotope,
        "SMEARING":smearing,
        "OUTPUTFILE_DECAY":"%s/output/%s/%s_RadioactiveDecayFrom%s.root"%(args.workdir,args.tag,isotope,vol_name)
        }

    ### Create Analysis config
    if (args.external and args.maxfilesperjob<0):
      template_conf = template_conf_externals
      for k,v in dict_replace_external.items():
        conf_filled =  re.sub(k,v,template_conf)
        template_conf = conf_filled
      outconfig = open("config/%s/cygnoconf_external_%s"%(args.tag,args.tag), "w") 
      outconfig.write(template_conf)
      submit_template = submit_template_externals
      for k,v in dict_replace_external.items():
        submitjob_filled =  re.sub(k,v,submit_template)
        submit_template = submitjob_filled
      outsubmitjob = open("submit/%s/submit_external_%s.sh"%(args.tag,args.tag), "w") 
      outsubmitjob.write(submitjob_filled)
      os.system("chmod +x submit/%s/submit_external_%s.sh"%(args.tag,args.tag))
      #cmd = "bsub -oo logs/%s/_external_%s submit/%s/submit_external_%s.sh"%(args.tag,args.tag,args.tag,args.tag)
      cmd = "qsub -o logs/%s/pbslog_external_%s submit/%s/submit_external_%s.sh -d /nfs/scratch/%s"%(args.tag,args.tag,args.tag,args.tag,getpass.getuser())
      print cmd
      #os.system(cmd)
      print("run cmd")
      subprocess.Popen([cmd], shell=True)
    
    elif (args.external):
      print("externals splitted")
      for ijob in range(0,njobs):
        #print templateconflist[ijob]
        for k,v in dict_replace_external.items():          
          conf_filled =  re.sub(k,v,templateconflist[ijob])
          conf_filled =  re.sub("IJOB",str(ijob),conf_filled)
          templateconflist[ijob] = conf_filled
        outconfig = open("config/%s/cygnoconf_external_%s_part_%s"%(args.tag,args.tag,ijob), "w") 
        outconfig.write(templateconflist[ijob])
        #print templateconflist[ijob]         
      for ijob in range(0,njobs):
        for k,v in dict_replace_external.items():
          submitjob_filled =  re.sub(k,v,templatesubmitlist[ijob])
          templatesubmitlist[ijob] = submitjob_filled
        outsubmitjob = open("submit/%s/submit_external_%s_part_%s.sh"%(args.tag,args.tag,ijob), "w") 
        outsubmitjob.write(templatesubmitlist[ijob])
        os.system("chmod +x submit/%s/submit_external_%s_part_%s.sh"%(args.tag,args.tag,ijob))
        #cmd = "bsub -oo logs/%s/log_external_%s_part_%s submit/%s/submit_external_%s_part_%s.sh"%(args.tag,args.tag,ijob,args.tag,args.tag,ijob)
        cmd = "qsub -o logs/%s/pbslog_external_%s_part_%s submit/%s/submit_external_%s_part_%s.sh -d /nfs/scratch/%s"%(args.tag,args.tag,ijob,args.tag,args.tag,ijob,getpass.getuser())
        print cmd
        #os.system(cmd)
        if args.retry:
          #Checking if the output and log exists
          if os.path.isfile('output/%s/out_external_%s_part_%s.root'%(args.tag,args.tag,ijob)):
            print('The output file output/%s/out_external_%s_part_%s.root exists and the job will not be resubmitted.'%(args.tag,args.tag,ijob))
	    continue
          else:
            print('Output file output/%s/out_external_%s_part_%s.root not found, resubmitted.'%(args.tag,args.tag,ijob))
            subprocess.Popen([cmd], shell=True)
	else:
          print("run cmd")
          subprocess.Popen([cmd], shell=True)
 
    else:
      template_conf = template_conf_decay
      for k,v in dict_replace.items():
        #print k+" "+str(v)
        conf_filled =  re.sub(k,v,template_conf)
        template_conf = conf_filled
      outconfig = open("config/%s/cygnoconf_%s_RadioactiveDecayFrom%s"%(args.tag,isotope,vol_name), "w") 
      outconfig.write(template_conf)
      submit_template = submit_template_decay
      for k,v in dict_replace.items():
        submitjob_filled =  re.sub(k,v,submit_template)
        submit_template = submitjob_filled
      outsubmitjob = open("submit/%s/submit_%s_RadioactiveDecayFrom%s.sh"%(args.tag,isotope,vol_name), "w") 
      outsubmitjob.write(submitjob_filled)
      os.system("chmod +x submit/%s/submit_%s_RadioactiveDecayFrom%s.sh"%(args.tag,isotope,vol_name))
      #cmd="bsub -oo logs/%s/log_%s_RadioactiveDecayFrom%s submit/%s/submit_%s_RadioactiveDecayFrom%s.sh"%(args.tag,isotope,vol_name,args.tag,isotope,vol_name)
      cmd ="qsub -o logs/%s/pbslog_%s_RadioactiveDecayFrom%s submit/%s/submit_%s_RadioactiveDecayFrom%s.sh -d /nfs/scratch/%s"%(args.tag,isotope,vol_name, args.tag,isotope,vol_name,getpass.getuser()) 
      print cmd
      #os.system(cmd)
      subprocess.Popen([cmd], shell=True)
  
