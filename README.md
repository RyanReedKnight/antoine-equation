# antoine-equation
Terminal application which can perform calculations with the Antoine Equation.

Program revolves around AnoineEOS class, which stores Antoine parameters associated with a set of chemical species, and performs
calculations with these parameters. The class uses a map to retrive the parameters associated with a chemical species, 
where the name of the species is the key used to get the species' parameters. Each instantance of the class should be associated with one 
source, e.g. if there are two papers which contain a set of Antoine parameters, a class should be instantiated for each paper.

This application has one instance of the AntoineEOS class, which uses the following paper as a source for its parameters. "T. Boublik, V. Fried, and E. Halla, "
"The Vapor Pressure of Pure Substances, Elisevier, Amsterdam, 1973"

As of now, the application gives the user the 5 following options. 

1. View full dataset, uses the AnotineEOS to_string() method to print a table conataining the chemical species' names in the first column, 
   followed by each species' associated A, B and C Antoine paramters, and the lower and upper temperature limit of these parameters. Above this table
   are the units used, and the equation (the Antoine Equation can use log base 10 or natural log). A citation of the source is printed below the table.
   ![Screenshot (75)](https://user-images.githubusercontent.com/54007504/160295526-e47a4c27-61ab-43d8-a592-59f1c71412e7.png)
2. List chemical species, prints a list of the chemical species stored in the instance of AntoineEOS.
3. Get saturation pressure of a species at a temperature, prompts user for the name of a chemical species, which must match one of the species names listed in 
   by the second option (case sensitive). The temperature range of the species is then displayed, and the user is pompted for a temperature (note: program does
   not stop user from entering temperature value outside of the given range).
   ![Screenshot (76)](https://user-images.githubusercontent.com/54007504/160300746-738c11b0-f5fa-42e9-9f13-e3bbbd2b25b2.png)
4. Get range of saturation pressure values within temperature range. Prompts user for the name of a chemical species, displays a range of sturated pressure
   values from the lower to upper temperature limit.
   ![Screenshot (77)](https://user-images.githubusercontent.com/54007504/160301091-4b04954e-bfc5-4fe5-b74e-3bbb0c7b9f37.png)
5. Exit program.

# Build and run
   Must have make installed and a C++ compiler. Clone the repository, enter the directory and use ```make```, 
and then run the resulting executible ```./antoine-eos```
