# Linear-Programmin-Simplex


<h1> About the project </h1>

Project created for study class - operational and logistical algorithms. Created within 1 day. Helps to plan means per product spent, when number of means is limited and our goal is to maximize profit.
For resolving this issue we use Simplex Algorihtm (which is not implemented by myself)

<h2> Stack <h2>

-Qt 5.15.2

-C++14 

-C

-qmake

<h2> Warning </h2>

As this project is a speed run project, quality of code is bad, also I haven't tested the building of project. Due to start configuartion as Widget Project in VS I couldn't split solver code quickly, I dind't investigated it, that's why files are so long and awful looking.
Language: polish only

<h2> Description </h2>

<h3>Welcome page </h3>
Give accordingly number of products and number of means, these parameters will be used to create input table

![alt text](https://github.com/Swistusmen/Linear-Programmin-Simplex/blob/master/screenshots/1.jpg)

>>Click Generuj tablice

<h3> Input table </h3>
Top row of the table- you can name the products. Left column- you can name means. Cells which have both product and mean- give means per 1 unit of product (integers), right column- limit of production, bottom row- profits per product

![alt text](https://github.com/Swistusmen/Linear-Programmin-Simplex/blob/master/screenshots/2.jpg)

>>Click Do wyniku

<h3> Input table </h3>

Products are placed accordingly to the table above, now give <= or >= and the number- you don't have to do it, but it let's you define bounds for number of product in output

![alt text](https://github.com/Swistusmen/Linear-Programmin-Simplex/blob/master/screenshots/3.jpg)

>>Click Do wyniku

<h3> Results </h3>

Funkcja celu- means goal function, next you have number of products under x1, x2 ... xn.

![alt text](https://github.com/Swistusmen/Linear-Programmin-Simplex/blob/master/screenshots/4.jpg)

<h3> How to interpret output? </h3>
x1 ... xn are number of final products. Goal function which is created from given input looks like this

```
goal fun= profit_1* x1+ ..... profit_n+ xn ->maximize
```

So for example above it'll be 

```
goal function= 30*x1+ 40*x2 -> maximize
equals:
170 000= 30*3000+ 40*2000
```

-> Create 3000 units of first product and 2000 units of second product


