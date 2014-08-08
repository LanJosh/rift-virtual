
Rift Virtual Conference
Virtual conferencing using the Oculus Rift and OpenSim.
 
***NOTE***: This research was supported in part by an appointment to the Student
Research Participation Program at U.S. Air Force Research Laboratory,
711th Human Performance Wing administered by the Oak Ridge Institute for 
Science and Education through an interagency agreement between the US. 
Department of Energy and USAFRL  

--------------------------------------------------------------------------------------
Revision History
--------------------------------------------------------------------------------------
YYYY/MM/DD| Author          | Description
----------|-----------------|-------------------------------------------------------
2014/08/08|Joshua Lan		| Final refactoring from SATE 2014. 
	      | 				| (see GitHub repo /LanJosh for version history up
		  |					| to this point).
		  |					|
---------------------------------------------------------------------------------------

Welcome to the Rift Virtual Conference codebase. This code interfaces a human users 
movements and a virtual representation of the user. The virtual representation is 
handled by OpenSim, with the viewer being CtrlAltStudio. The comments within the 
program are important to note and this readme is NOT a suitable replacement for working
in the codebase to increase familiarity. Do not make the mistake of ignoring comments. 

However, this is written to the audience of new developers at Discovery Lab (who are 
generally complement new developers in general). As no members of the RVC team from 
SATE 2014 seem to be returning, this is written with a sledgehammer approach. I have 
attempted to be as exhaustive as possible in writing this while pointing you towards 
resources to teach yourself. If you plan on using this readme or extending it, note
that this is written in for *Github flavored* markdown. 

 
#INTERFACES:

Files preceded with an 'I' dictate interfaces written for this program. These
interfaces are generally filtered in each filter by the denomination "Interfaces". Any 
changes to the interfaces should be carefully considered as it will take a long time to
reflect the change in the codebase. Interfaces should all contain contracts for their 
methods. 

The IEvent interface (see IEvent.h) defines the **baseline** for an event handler for 
virtual conferencing. The event handler should cause reactions in virtual world 
dependent upon events in the physical world. The current polling structure is dependent
upon processing speed. Different implementations of turning and movement are supported
to varying degrees by the event handler.

The IPedo interface (see IPedo.h) extends the IEvent interface. This interface defines 
methods allowing for turning and movement. Movement in this interface is supported by 
using a pedometer algorithm. 

The IThresh interface (see IThresh.h)  extends the IEvent interface. This interface
provides the same functionality as IPedo, but differs in philosophy. This uses 
threshold values for entering a state rather than IPedo's usage of event replication.

The IList interface (see IList.h ) defines a representation of head position using two 
lists. This is to be used in junction with implementation of the IThresh interface. 
This is segmented from the IThresh interface in case this must be used in junction with
a different virtualization technology. 

The IRift interface (see IRift.h) defines connections to the Oculus Rift and methods to
pull data from the Rift sensors. This was created to make a single point of control
for changes involving the Rift (our development was on deprecated hardware/software).
Hopefully this will make changing to updated versions trivial for future teams.

 
#IMPLEMENTATIONS:

Implementations are all forward declared within header files with the same name as the 
file containing the implementation. The implementations are carefully considered, if 
changes are to be made, consider seriously why you wish to make these changes and think
if your proposed changes may be different enough to warrant another class. With the DLab
wishing for massive modularity with different hardware and with different software on a
moments notice, the code will benefit from being extremely segmented. Make sure to 
consider the project changes that will inevitably occur working at DLab. 

RVC implements the IRift interface, EventInterfacing implements the IPedo interface, and
EventInterfacing1 implements the IThresh interface (note the strange naming convention
here--these two event interfacing classes are NOT related beyond IEvent).  


#CONVENTIONS AND TIPS:

The codebase adapts several conventions those new to programming may not understand or
have yet seen. Some conventions were developed and put in place simply because of the 
environment Discovery Lab is. In order to allow future Rift teams to bypass some of the
headaches RVC 2014 ran into, here is a compiled list of tips for reading/using the code
base, making good changes, and getting acclimated to the high speed of DLab.

1. NAMING CONVENTIONS:
I used Apps-Hungarian notation to show attributes of objects to ensure the team would
be able to notice all dangers/match types. I suggest that future teams do the same. 
For example, 'p' is prefixed to all pointers in our codebase. Pointers are tricky, and
it is certainly not a bad idea to take note of where they are, so adding a 'p' can save
time. But adding an 'i' infront of every int is mostly likely overkill (if you can see
where it would not be, you probably don't need me to explain Apps-Hungarian).Think through 
variable names (well pretty much all names). Google's C++ code style conventions 
(http://google-styleguide.googlecode.com/svn/trunk/cppguide.xml)are a good place to read some 
more about this. It may take time to think about a variable name through the scope of many different 
devs eyes but it will pay off in the end.

2. DEVELOPMENT STRUCTURE:
We used the Agile Development framework and it worked fairly well to our favor. I 
suggest using a framework that incorportates contact with other teams and frequently
updates the Director to make sure the direction is good and you can draw upon the 
multitude of resources at Discovery Lab. Discovery Lab expects frequent updates and
progress reports (a real hacker methodology) so it's not a bad idea to push out demos
quickly to make these update deadlines--then refactor code when you have down time. 
It is better to not spend a week planning what could be best or most elegant and
miss a deadline when you can make a version with solid logic and demonstrative capabilities 
and refactor/optimize when you have down time. 
**NOTE**: I am not saying this is a best practice or a philosophy you should always apply,
take note of the situation you are in before you do something. This is simply something
that worked for us at Discovery Lab. 

3. CODING STRUCTURE:
This was discussed earlier, but highly segmented code works very well at Discovery Lab with
how much project scope changes and with visitors frequently coming in, expected demonstrations.
With this need to be so quickly adaptable and able to throw things together, having code that 
splits everything into a nice container allows for many different things to be made from the 
parts. When coding something, briefly ask yourself how it fits into the bigger picture and what
it encompasses. The answer to this will likely give you some insight about what you should name 
it and where you should put it. 

#SAMPLES:

We unfortunately did not have time to put together full samples in different projects to show off
dependencies and make fancy graphics to show you. However, Samples.cpp includes code that demonstrates
just about everything we did and how we did it. To run them, you can simply uncomment them in the 
main.cpp file (a little more difficult than if we had seperated them into 9 projects, but still simple
enough to do easily). 
