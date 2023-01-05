# Overview :

&nbsp;&nbsp;&nbsp;This program was made for a school project in advanced algorithms, we were asked to implement an expert system using only linked lists, the program is pretty basic nothing fancy, and the code is -a bit- messy, but all in all I think I learned some new things.

<p align="center">
  <img src="https://i.imgur.com/n3tfK1v.png" alt="Main Menu"/>
</p>

# How to use :

* First time starting the program it is a must to execute the first 2 functions before proceeding **only once**, as they allocate the memory needed for the facts and rules bases. The program will crash sometimes if you executed the third or the fourth functions directly.
  + Why only once you may ask ? It's because the program will overwrite whatever data found in the bases in the second execution.  

* After executing the first two functions, you add rules and facts with the third and fourth functions.

* The four next function do exactly what the say.

* And now for the inference engine, first it shows you the available list of rules then it asks first for a number from the user to enter, this number represents the number of conditions of a certain rule, after giving an input the program will trigger a function that demands the user to enter a list of conditions, the user can be guided by the list of rules already shown to write the conditions of a path he selects.

    +  I tried experimenting with a function that lets the user enter only the indexes of the conditions he wants, as it's a hustle for the user to write all of that by himself, and in case of him mispelling something the program will not give the result wanted. Unforunately my program was crashing for some reason and I kept things like this.

# Some improvements needed :

  * [ ] Update the inference engine to let it use indexes.
  * [ ] Use file handling to save the data and import it each time the program is executed.
