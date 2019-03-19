## Tracking progress of Loops in Python with Bars using TQDM ## 

from tqdm import tqdm
import time

# pip install tqdm 


for i in tqdm(range(int(1e2))):
	## Some Logic for the loop ## 
	pass



modules = tqdm(["Module 1", "Module 2", "Module 3", "Module 4", "Module 5"])
for module in modules:
	time.sleep(0.25)
	modules.set_description("Current Module: %s" % module)
	## Some Module logic goes here ## 



modules = tqdm(["Module 1", "Module 2", "Module 3", "Module 4", "Module 5"])
for module in modules:
	modules.set_description("Module: %s" % module)
	sub_modules = tqdm(["Sub Module 1", "Sub Module 2", "Sub Module 3"])
	for sub_module in sub_modules:
		time.sleep(0.25)
		sub_modules.set_description("Sub Module: %s" % sub_module)
		## Sub Module logic goes here ## 

