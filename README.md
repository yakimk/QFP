# QFP - Qt Function Plotter

QFP is a simple graphical application used for function plotting. It could be used to plot different functions, mark zeroes of functions and their intersections. 

[Application preview](img/preview.png)

## Requirments
- [Qt5](https://github.com/qt/qt5)
- [qmake](https://doc.qt.io/qt-6/qmake-manual) (should be in Qt package)
- [g++](https://gcc.gnu.org/releases.html)  >= 11.4
- [make](https://www.gnu.org/software/make/)

## Building
To build application run 
```
qmake; make
```

Then you'l be able to start it with the `QtFunctionPlotter` executable in the `QFP` directory.


## Using
Upon opening QFP, enter a function in one of the coresponding textfields on the left side of the screen. Then press "ENTER" on your keyboard or a button "Apply Functions" underneath the textfields. There is a maximum of 5 functions that could be plotted at the same time.

You can plot polynomial functions and their quotients (rational functions):
- `2 + 3` constant function $f(x) = 5$.
-  `x ** 2 + 3 * (4 - x) - 0` would be $f(x) = x^2 + 3 * (4-x) - 0.$
- `(x + 1)/(x + 3)` rational function $f(x) = \frac{x+1}{x+3}.$

#### Special functions
Also some other special mathematical functions could be used

| Name | Math equivalent function |
|---------------|--------------|
| sin(x)        | $sin(x)$  |
| cos(x)        | $\cos(x)$  |
| tan(x)        | $\tan(x)$  |
| asin(x)       | $\arcsin(x)$ |
| acos(x)       | $\arccos(x)$ |
| atan(x)       | $\arctan(x)$ |
| sinh(x)       | $\sinh(x)$ |
| cosh(x)       | $\cosh(x)$ |
| tanh(x)       | $\tanh(x)$ |
| exp(x)        | $\exp(x)$  |
| log(x)        | $\log(x)$  |
| log10(x)      | $\log_{10}(x)$ |
| sqrt(x)       | $\sqrt{x}$ |
| fabs(x)       | $\|x\|$      |
| ceil(x)       | $\lceil x \rceil$ |
| floor(x)      | $\lfloor x \rfloor$ |
| round(x)      | $\operatorname{round}(x)$ |


Examples
- `log10(x ** 2)` would equal $\log_{10}(x^2)$
- `fabs(x - 2)/sqrt(tanh(x))` would equal $\frac{|x-2|}{\sqrt{\tanh(x)}}$

#### Zeroes and intersections
You could toggle display of zeroes of the plotted functions or their intersections with the coresponding button on the left side of the screen.
Both zeroes and intersections are being calculated with a naive algorithm that checks if the difference of values is less than `epsilon` for every point in the defined domain and each step.

To change domain or redefine the settings (`epsilon` or `step` parameters) of this calculation, enter a chosen value in a coresponding textfield and then replot the functions, either by pressing "Apply Functions" or by pressing "ENTER" on your keyboard. 

### Possible todos
- [ ] area coloring under a function plot
- [ ] aproximate integral or derivate at some point
