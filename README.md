# IPS-PROD

# How to use the program ?
## Building the program
Make sure armadillo is installed on your machine, then run `make`
## Making a 3D plot of the density
Make sure you have POV-Ray installed, with extra package povray-includes if you use Debian, then run `make 3D`
## Making a 2D plot of the density
Make sure you have Python installed along with matplotlib, and that Python is available by typing `python` in the terminal. Otherwise, if for example you have to type `python3` to run Python, edit the `Makefile` to set `PY=python3` then run `make 2D`
## Making both
`make images`

# How to use documentation ?
## Updating documentation
`doxygen Doxyfile`

## Reading the documentation with the browser
`firefox ./doc/html/index.html &` (assuming your browser is firefox)

# Viewing the visual presentation of the project
`firefox pres/index.html &`
