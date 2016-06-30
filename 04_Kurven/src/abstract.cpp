//
// This source code is property of the Computer Graphics and Visualization 
// chair of the TU Dresden. Do not distribute in modified or unmodified form! 
// Copyright (C) 2016 CGV TU Dresden - All Rights Reserved
//
#include "abstract_curve.h"

// Initialize the curve and store a reference of the control points
abstract_curve::abstract_curve(std::vector<point2d> &control_points): control_points(control_points)
{
	t_min = 0;
	t_max = 1;
}

abstract_curve::~abstract_curve() {}


// Evaluate the curve at "t"
point2d abstract_curve::evaluate(double t)
{
	point2d sample(0.0, 0.0);

	/**************
	Task 4.1.1.    Implement the functionality to evaluate a point on the curve
	               at the parameter value "t". The point is calculated by summing
	               all control points weightened with their basis function at "t".
	               Store the result into the variable "sample". To get the ith control 
	               point use "control_points[i]". You can get the number of
	               control points with "control_points.size()". Use the command 
                   "evaluate_basis" to get the basis function value for a control
                   point at "t". The point2d class supports operations such as addition 
	               or multiplication with a scalar value. Below are some sample codes.
	Aufgabe 4.4.1. Implementieren Sie die Auswertung eines Punktes auf der Kurve fuer
	               den Parameterwert "t". Ein Kurvenpunkt ist die Summe aller Kontroll-
                   Punkte, gewichtet mit deren Basisfunktionen bei "t". Speichern Sie
                   das Ergebnis in der Variable "sample". Um den i-ten Kontrollpunkt zu
                   erhalten nutzen Sie "control_points[i]". Die Anzahl der Kontrollpunkte
                   koennen Sie mittels "control_points.size()" ermitteln. Verwenden Sie die
	               Methode "evaluate_basis" um den Wert der Basisfunktion eines Kontrollpunktes
	               an der Stelle "t" zu erhalten. Die point2d-Klasse unterstuetzt Operatoren 
				   wie Addition oder Multiplikation mit skalaren Werten. Einige Beispiele:

				   // define a point
				   point2d pnt(0.0, 0.0);
				   // define another point
				   point2d pnt2 = 2.0*pnt;
				   // add points
				   pnt += 3.0*pnt2;
   **********/

	for (int i = 0; i < control_points.size(); i++){
		sample += evaluate_basis(i,t) * control_points[i];
	}

	return sample;
}



// Get the minimum value of the domain
double abstract_curve::get_min_t()
{
	return t_min;
}


// Get the maximum value of the domain
double abstract_curve::get_max_t()
{
	return t_max;
}

// get casteljau t
double abstract_curve::get_casteljau_t(){

	return casteljau_t;
}



// Get a constant list of control points
const std::vector<point2d>& abstract_curve::get_control_points() const
{
	return control_points;
}




// Shall be called whenever the control point set changes
void abstract_curve::control_points_updated()
{
	// ... does nothing and should be specified in inherited classes
	// if needed.
}




// Put a text into the stream "stream" which will be displayed
// in the main window
void abstract_curve::set_text(std::stringstream &stream)
{
	// ... does nothing and should be specified in inherited classes
	// if needed.
}
