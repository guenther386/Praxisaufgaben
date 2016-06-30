//
// This source code is property of the Computer Graphics and Visualization 
// chair of the TU Dresden. Do not distribute in modified or unmodified form! 
// Copyright (C) 2015 CGV TU Dresden - All Rights Reserved
//
#include "hermite_spline.h"
#include <math.h>


// Initialize the curve and store a reference of the control points
hermite_spline::hermite_spline(std::vector<point2d>& control_points): abstract_curve(control_points)
{

}




// Evaluate the curve at "t"
point2d hermite_spline::evaluate(double t)
{
	int n = control_points.size();

	/*********
	Task 4.1.5.    Implement the evaluation of a spline point. A point
	               is built using the control points and their tangents. You
	               only have to do the calculation for one spline segment.
	               See the script for the calculation of points for one segment.
	Aufgabe 4.1.5. Implementieren Sie die Auswertung eines Spline-Punktes. Dieser
	               wird ueber die Kontrollpunkte und Tangenten bestimmt. Die Berechnung
                   soll lediglich fuer ein Segment erfolgen. Im Skript finden Sie
                   genauere Informationen dazu.
   ***********/


	if (n<3)
		return point2d(0.0, 0.0);

	point2d q0 = control_points[0];
	point2d q1 = control_points[n - 1];
	point2d m0 = control_points[1] - control_points[0];
	point2d m1 = control_points[n - 1] - control_points[n - 2];


	// Remove and replace me with the right return value
	return (q0*evaluate_basis(0, t)) + (m0*evaluate_basis(1, t)) + (m1*evaluate_basis(2, t)) + (q1*evaluate_basis(3, t));

}




// Evaluate a basis as a function of the control point "point_num"
// (counted from zero) and the domain parameter t
double hermite_spline::evaluate_basis(int point_num, double t)
{

	/***********
	Task 4.1.5.    Implement the evaluation of the basis function for the
	               point "point_num" at "t". You will find the formulas for
	               one segment directly in the script. Use the appropriate
	               formula for the right value of "point_num".
	Aufgabe 4.1.5. Implementieren Sie die Auswertung der Basisfunktion des
	               Punktes "point_num" an der Stelle "t". Sie finden die
                   Formeln fuer ein Segment im Skript. Verwenden Sie fuer
                   jeden Wert von "point_num" die entsprechende Berechnungs-
                   Vorschrift.
	***********/



	switch (point_num){
		default:
			return 0;

		case 0:
			return pow(1 - t, 2)*(1 + 2 * t);
		case 1:
			return t*pow(1 - t, 2);
		case 2:
			return -pow(t, 2)*(1 - t);
		case 3:
			return (3 - 2 * t)*pow(t, 2);

	}

}



// Set debug text
void hermite_spline::set_text(std::stringstream &stream)
{
	stream<<"Type: Hermite (simple)";
}