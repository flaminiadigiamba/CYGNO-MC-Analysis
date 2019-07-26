#! /usr/bin/env python
import os
import sys
import argparse
import re
from ROOT import *
import glob
import subprocess


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

args = parser.parse_args()
print args 

os.system("mkdir -p logs/"+args.tag)
os.system("mkdir -p submit/"+args.tag)
os.system("mkdir -p output/"+args.tag)
os.system("mkdir -p config/"+args.tag)

mass = {
"foo":-999,
"Shield0":86539.5,
"Shield1":16113.5,
"Shield2":57782.8,
"Shield3":8738.24,
"cad_camera_carter_physical":14.0275,
"cad_cameras_all_physical":32.7229,
"cad_fc_support_physical":29.77,
"cad_turns_support_physical":34.7248,
"cad_field_cage_physical":42.4915,
"cad_gem_support_physical":15.7757,
"cad_gem_physical":0.4684,
"cad_cathode_frame_physical":56.5125,
"cad_cathode_physical":0.98408,
"TPC_gas":0.98408,
"CYGNO_gas":2*0.810438

}

splittedlists = []

#nlists = 0
#for l in os.listdir("lists/"+args.listdir):
#  nlists +=1
nlists = len(glob.glob1("lists/"+args.listdir,"*.txt"))

print nlists

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
      splittedlistfilename = "lists/"+args.listdir+"/split/list_external_shieldgeo_"+args.tag+"_part_"+str(jj)+".list"
      splittedlist = open(splittedlistfilename,"a+")
      splittedlist.write(line)
      if ( modulo == 0 or jf+1==nfiles ):
          splittedlist.close()
          splittedlists.append(splittedlist)
          jj+=1
      jf+=1
  nfiles = jf+1


njobs = len(splittedlists)
ijob=0
print("n jobs = %s"%njobs)
inputconf = open(args.inputconf,"r")
templateconflist = []
templatesubmitlist = []

for line in inputconf:
  template_conf_decay =  """externalflux 0
CYGNO_gas_mass 1.6208755
mass MASS
smearing SMEARING
activity ACTIVITY
half_life HALFLIFE 
smearing SMEARING
filelist lists/LISTDIR/list_ISOTOPE_RadioactiveDecayFromVOLUME.txt
root_out OUTPUTFILE_DECAY"""
  #print template_conf

  if (args.maxfilesperjob)<0:
    template_conf_externals =  """externalflux 1
CYGNO_gas_mass 1.6208755
externalflux_value FLUX
shield0_thickness THICK0
shield1_thickness THICK1 
shield2_thickness THICK2 
shield3_thickness THICK3 
smearing SMEARING
filelist lists/LISTDIR/list_external_SHIELDGEO.txt
root_out OUTPUTFILE_EXT\n"""
  
    submit_template_decay = """#!/bin/bash
#PBS -j oe  
#PBS -o logs/"""+args.tag+"""/pbslog_ISOTOPE_RadioactiveDecayFromVOLUME
cd WORKDIR
pwd
time ./CYGNOAnalysis config/"""+args.tag+"""/cygnoconf_ISOTOPE_RadioactiveDecayFromVOLUME  > logs/"""+args.tag+"""/Analysis_log_ISOTOPE_RadioactiveDecayFromVOLUME"""+"""\n"""

    submit_template_externals = """#!/bin/bash
#PBS -j oe 
#PBS -o logs/"""+args.tag+"""/pbsloglog_external_shieldgeo"""+args.tag+"""
cd WORKDIR
pwd
time ./CYGNOAnalysis config/"""+args.tag+"""/cygnoconf_external_shieldgeo_"""+args.tag+""" > logs/"""+args.tag+"""/Analysis_log_external_shieldgeo"""+args.tag+"""\n"""

  else:
    for ijob in range(0,njobs):
      template_conf_externals =  """externalflux 1
externalflux_value FLUX
CYGNO_gas_mass 1.6208755
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
#PBS -o logs/"""+args.tag+"""/pbslog_external_shieldgeo"""+args.tag+"""_part_"""+str(ijob)+"""
cd WORKDIR
pwd
time ./CYGNOAnalysis config/"""+args.tag+"""/cygnoconf_external_shieldgeo_"""+args.tag+"""_part_"""+str(ijob)+""" > logs/"""+args.tag+"""/Analysis_log_external_shieldgeo"""+args.tag+"""_part_"""+str(ijob)+"""\n"""
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

  if not args.external and not line.startswith("#"):
    vol_name = line.split()[0]
    isotope = line.split()[1]
    activity = line.split()[2]
    smearing = line.split()[3]
    halflife = line.split()[4]
  elif args.external and not line.startswith("#"): 
    flux = line.split()[0]
    thick0 = line.split()[1]
    thick1 = line.split()[2]
    thick2 = line.split()[3]
    thick3 = line.split()[4]
    smearing = line.split()[5]
    
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
	"OUTPUTFILE_DECAY":"%s/output/%s/%s_RadioactiveDecayFrom%s.root"%(args.workdir,args.tag,isotope,vol_name),
	}

    ### Create SABREAnalysis config
    if (args.external and args.maxfilesperjob<0):
      template_conf = template_conf_external
      for k,v in dict_replace_external.items():
        conf_filled =  re.sub(k,v,template_conf)
      outconfig = open("config/%s/cygnoconf_external_shieldgeo_%s"%(args.tag,args.tag), "w") 
      outconfig.write(conf_filled)
      submit_template = submit_template_external
      for k,v in dict_replace_external.items():
        submitjob_filled =  re.sub(k,v,submit_template)
        submit_template = submitjob_filled
      outsubmitjob = open("submit/%s/submit_external_shieldgeo_%s.sh"%(args.tag,args.tag), "w") 
      outsubmitjob.write(submitjob_filled)
      os.system("chmod +x submit/%s/submit_external_shieldgeo_%s.sh"%(args.tag,args.tag))
      #os.system("bsub -oo logs/%s/_external_shieldgeo_%s submit/%s/submit_external_shieldgeo_%s.sh"%(args.tag,args.tag,args.tag,args.tag)
      cmd = "qsub submit/%s/submit_external_shieldgeo_%s.sh"%(args.tag,args.tag) 
      print cmd
      #os.system(cmd)
      subprocess.Popen([cmd], shell=True)
    
    elif (args.external):
      print("debug")
      for ijob in range(0,njobs):
        #print templateconflist[ijob]
        for k,v in dict_replace_external.items():          
          conf_filled =  re.sub(k,v,templateconflist[ijob])
          conf_filled =  re.sub("IJOB",str(ijob),conf_filled)
          templateconflist[ijob] = conf_filled
        outconfig = open("config/%s/cygnoconf_external_shieldgeo_%s_part_%s"%(args.tag,args.tag,ijob), "w") 
        outconfig.write(templateconflist[ijob])
        #print templateconflist[ijob]         
      for ijob in range(0,njobs):
        for k,v in dict_replace_external.items():
          submitjob_filled =  re.sub(k,v,templatesubmitlist[ijob])
          templatesubmitlist[ijob] = submitjob_filled
        outsubmitjob = open("submit/%s/submit_external_shieldgeo_%s_part_%s.sh"%(args.tag,args.tag,ijob), "w") 
        outsubmitjob.write(templatesubmitlist[ijob])
        os.system("chmod +x submit/%s/submit_external_shieldgeo_%s_part_%s.sh"%(args.tag,args.tag,ijob))
        #os.system("bsub -oo logs/%s/log_external_shieldgeo_%s_part_%s submit/%s/submit_external_shieldgeo_%s_part_%s.sh"%(args.tag,args.tag,ijob,args.tag,args.tag,ijob)
        cmd = "qsub submit/%s/submit_external_shieldgeo_%s_part_%s.sh"%(args.tag,args.tag,ijob)
        print cmd
        #os.system(cmd)
        subprocess.Popen([cmd], shell=True)
    else:
      template_conf = template_conf_decay
      for k,v in dict_replace.items():
        conf_filled =  re.sub(k,v,template_conf)
      outconfig = open("config/%s/cygnoconf_%s_RadioactiveDecayFrom%s"%(args.tag,isotope,vol_name), "w") 
      outconfig.write(conf_filled)
      submit_template = submit_template_decay
      for k,v in dict_replace.items():
        submitjob_filled =  re.sub(k,v,submit_template)
        submit_template = submitjob_filled
      outsubmitjob = open("submit/%s/submit_%s_RadioactiveDecayFrom%s.sh"%(args.tag,isotope,vol_name), "w") 
      outsubmitjob.write(submitjob_filled)
      os.system("chmod +x submit/%s/submit_%s_RadioactiveDecayFrom%s.sh"%(args.tag,isotope,vol_name))
      #os.system("bsub -oo logs/%s/log__%s_RadioactiveDecayFrom%s submit/%s/submit_%s_RadioactiveDecayFrom%s.sh"%(args.tag,isotope,vol_name,args.tag,isotope,vol_name))
      cmd ="qsub  submit/%s/submit_%s_RadioactiveDecayFrom%s.sh"%(args.tag,isotope,vol_name) 
      print cmd
      #os.system(cmd)
      subprocess.Popen([cmd], shell=True)

