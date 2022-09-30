# Shipping-Company

## 💡 Description
<div>

- &nbsp;The Company working hours are from 5:00 to 23:00.
- &nbsp;A shipping company needs to handle cargo delivery the most efficient and profitable way.
The company needs to automate the cargo-truck assignment process to achieve good and fair use
of its trucks.
- &nbsp;The program should receive all information to be simulated from an input file and
produce an output file that contains some information and statistics.
The input file format below

![image](https://user-images.githubusercontent.com/110634473/193276464-d69f45fd-de4a-4336-9de2-5c4e2f075cb6.png)

The output file format below:  
(CDT:Cargo Delivery Time ,PT:Cargo Prepartion Time,WT:Cargo Wait Time,TID:Truck Carrying Cargo Id)

![image](https://user-images.githubusercontent.com/110634473/193277467-714560b1-30fa-45a7-aecc-e1a83ccf2d56.png)


- &nbsp;There are 3 types of cargos:
  - &nbsp;VIP cargos: must be assigned first before other cargos.
  - &nbsp;Special cargos:cargos to need special trucks like frozen cargos or chemical cargos,... etc
  - &nbsp;Normal cargos: for all other cargos.
- &nbsp;There are 3 types of Trucks:
  - &nbsp;VIP trucks: are trucks that are used basically for VIP cargos.
  - &nbsp;Special trucks: are trucks that are equipped to carry special cargos.
  - &nbsp;Normal trucks
 - &nbsp;That's the assignment criteria:
   - &nbsp;Assign VIP cargos are assigned to VIP trucks THEN normal
trucks THEN special trucks.This means that we do not use normal trucks unless
all VIP trucks are out, and we do not use special trucks unless trucks of all other
types are out.
   - &nbsp;Assign special cargos using the available special trucks ONLY. If no
special truck is available, wait until one comes back.
   - &nbsp;Assign normal cargos using any type of trucks EXCEPT special trucks.
First use the available normal trucks THEN VIP trucks (if all normal trucks are
out).
   - &nbsp;If a cargo cannot be assigned on the current hour, it should wait for the next
hour. On the next hour, it should be checked whether the cargo can be assigned
now or not. If not, it should wait again and so on. 
- &nbsp;The program has 3 modes :
  - &nbsp;Interactive mode:This mode displays at each hour the status of all the trucks and cargos of the company whether they are inside or outside.
  - &nbsp;Step by step mode:is identical to the interactive mode except that after
each hour, the program waits for one second then resumes automatically.
  - &nbsp;Silent Mode:The program produces only an output file.
 - &nbsp;The simulation function stops when there are no more events and all cargos
are delivered.
 </div>


## 🔧How To Use

 - &nbsp;First:Prepare your input file with the same format provided above.
 - &nbsp;Second:Run the program on visual studio 2019 (if you wanna use another version check how to retarget the project).
 - &nbsp;Third:Run The Program and write your input file name (with .txt) and the name you want for the output file (with .txt).
 - &nbsp;Only if you are in interactive mode,Press enter to move to the next hour.
 - &nbsp;Congratulations,the program will starts to work now.
 - &nbsp;There are some preprepared input and output files provided.

## 🧨Important Note

- &nbsp; In input file:This program has no auto promotion limit (days), MaxW (hours),cancellation event example and promotion event example.
- &nbsp; In output file:This program has no auto promoted cargos.
 
 ![image](https://user-images.githubusercontent.com/110634473/193285493-d79d6424-7aed-48c7-bd1d-c957e253eccc.png)





