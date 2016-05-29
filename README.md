# AVC-Challenge


Here is our AVC checklists
###Week 1 Checklist

- [x]: All: Complete AVC Plan
- [x]: Sam: Organise follow up group meeting and ensure plan is completed and signed by all members /n
- [x]: Quan, Jules: Write code for straight forward movement of the robot (as we cant use example file)
- [x]: Quan : Ask Arthur and tutors how to get the ipaddress of the RPI for the future and write it down on the commandline file
- [x]: Quan : Ask Arthur and tutors where to store code-files on the RPi and how to import the RPi library
- [x]: Quan : find out how the makefile works 
- [x]: Quan, Jules: Try to get the RPi emulators running at home.
### week 1 comments (to be updated)

** makefile is a list of commands for the shell (in our case UNIX Shell) sort of like a book of instructions the shell follows so we don't have to type the same commands repeatedly. The command "make" will execute the commands listed in the makefile. 

** Note that Arthur's makefile contains the compiling command, that's why we have to execute it first before our AVC txt code so it compile first and add the new changes.

** command "ifconfig" gives you the ip address of the RPi, it has to be connected to the network though and constantly update for the code [obviously you either need to connect the RPi from the station computer (one at the entrance) or to the monitor and keyboard in any PC]

-Jules has asked received the method to locate the IPAddress on the RPi, and it has been updated onto the commandlineinstructions file
-Jules has also found out how the makefile works
-Jules has also wrote the initial code
- Emulator seems to not be of help, as we actually don't know what to do with it just yet

###Week 2 checklist

- [x] Sam: Arrange follow up meeting, outline plan for following week
- [x] Jules, Quan: Update github with progress from last meeting
- [x] Nikhil, Hamish: Assemble hardware, prototype design for chassis 

###Week 2 comments 

- Quan and Jules have updated gitHub
- Hardware team have not finished their designs, was carried onto week three
- Little to do as there was the mid term break

###Week 3 checklist (Quadrant 1)

- [x] (All) Write Methods section (robot description)
- [x] Sam: overlook team progress, plan for following week, keep github updated
- [x] Jules: Develop robot movement code and networking code
- [x] Quan:  Tidy up and refine robot movement code, and also networking code if have time
- [x] Hamish, Nikhil: Start building the chassis, characterise motors, prototype designs & hardware

** We started building the actual robot with the final concept later than we expected.
** network code was created by sam instead, Quan has implemented this portion into the PI code.
**Robot code still jittery and as we didnt have time to fix it since lab times were only 2 hours. This task will be carried on towards towards next week
** We essentially stuck with the pre-made robot for testing and later constructed the actual product when most of the testing was        done. 

###Week 4 checklist (Quadrant 2)

- [x] (All): Write Discussion/Results section
- [] Sam: provide help to both hardware and software where needed, ensure members are on track for progress report
- [x] Jules: further develope movement code for quadrant 2 & 3
- [x] Quan: refine movement code to ensure quadrant 2 completion and develope for quadrant 3
- Quan and Jules swapped roles essentially.
- [x] Hamish, Nikhil: finalise designs and continue printing chassis parts, designs IR sensor mounts

** The concepts were all finalised. The actual 3D models were different from the ones draw as a hard copy. We basically simplified it    down due to time constraints and resources. 
** Due to bugs within the hardware and fault within the library, we didnt manage to develop any quadrant 3 code.
** The bot turns smoothly after some debugging due to regression issues (3 hours taken)
** Printing was delayed as there were a limited amount of printers and one printer was dysfunctional. This further decreased the         amount of time we could work on our project pushing us back further.

###Week 5 checklist (Quadrant 3) (Progress Report Due)

- [x] (All): Hand in progress report/re-write final report based on feedback 
- [] Sam: continue providing help to both hardware and software, ensure github is maintained
- [x] Jules: continue developing movement code for quadrant 3 and adapt for quadrant 4
- [x] Quan: continue developing movement code for quadrant 3 and adapt for quadrant 4
- [x] Hamish, Nikhil: continue/finish printing parts for chassis, make any changes necessary changes for better performance

** Printing took more than 10hours for all the parts. 
** There were regression errors once again due to unknown issues where the handling of the wheel was different to last weeks' test despite no changes to the code. Possibly due to inconsistancy as the wheels were too small to provide consitant speed due to friction and pressure. To do this we changed the wheels and updated constants so that handling was fixed.

** Regression testing and code updating was done. The robot is handling correctly around quadrant 2 and 3. However quadrant 3 yields 
inconsistant results which needed to be fixed. 

** Made minor miscalculations which causes a major loss in time as we only had a few days left and the limited printers once again. 

** Becaue of this a new part needed to be made. It was a base for the the Raspberry Pi to it on. 

** IR sensor hinges took too long to make due to high demands and queue line of the 3D prints, and the software also behind schedule 
due to various bugs means that quadrant 4 was decided to be optional and lower priority. We will only do it if we have time
###Week 6 checklist (Quadrant 4)

- [] (All): continue re-writing final report based on progress feedback
- [] Sam: ensure both hardware and software are meeting requirments, continue providing help and keep github updated
- [] Jules: finish code for quadrant 4 and 3 so robot and traverse maze
- [x] Quan: fix any bugs in code as well as supply help for movement code quadrant 4
- [x] Hamish, Nikhil: finish printing hardware and assemble 

** Made a lot of last minute changes. So of the parts were too flimsy but we fixed the issues with various methods.
** quadrant 1-2-3 is working with the newly assembled robot. However methods for quadrant 4 was changed and quadrant 4 code has been initialized, no clue if it will work or flop.

** we havent implemented quad 4 code and therefore it is not finished
