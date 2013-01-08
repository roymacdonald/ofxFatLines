ofxFatLines
===========

Introduction
------------
openFrameworks addon for drawing nicely antialiased lines of any width.
Based on VaseRenderer done by Chris Tsang,
http://artgrammer.blogspot.com/2011/06/vaserendererdraft12.html
http://www.codeproject.com/Articles/226569/Drawing-polylines-by-tessellation

This addon is quite easy to use.
Check the examples.
It provides two functions:
The following draws polylines.

`void ofxFatLine( const ofVec2f* P,   //A pointer to a vector containing the anchor points of the polyline.
	const ofFloatColor* C,			  //A pointer to a vector containing the color data for each anchor point.
 	const double* weight,			  //A pointer to a vector containing the width of the polyline at each anchor point.
  	int size_of_P, 					  //Total number of anchor points.
  	const ofxFatLineOptions* option,  //The options for the polyline. Read bellow.
  	bool triangulation);		 	  //Mainly a debuging option, it renders the teselation of the polyline.`
  	
void ofxFatLine( const ofVec2f* P, const Color* C, const double* weight, int size_of_P, const ofxFatLineOptions* options);//The same as above but triangulation is false.`
The following draws a line segment:
`void ofxFatSegment(const ofVec2f& P1, const ofVec2f& P2, 	//Anchor points of the line segment.
						  const Color& C1, const Color& C2, //Colors at each anchor point.
						  double W1,double W2,				//Width at each anchor point.
						  const ofxFatLineOptions* options) // the options.`
ofxFatLineOptions 
`struct ofxFatLineOptions{	//set the whole structure to 0 will give default options
	char joint; 		//Joint type 
						//miter 0
						//bevel 1
						//round 2
	char cap;   		//Cap type
						//butt   0
						//round  1
						//square 2
						//rect   3
	bool feather; 		// edge feather enable
	double feathering;  //edge feathering amount 
	bool no_feather_at_cap;
	bool no_feather_at_core;
	};
`

Licence
-------
Please read licence.md

Installation
------------
Clone into your openFrameworks/addons folder.

Dependencies
------------

Compatibility
------------
Works with of 0073 onwards. Yet it should work with previous versions, probably down to 0071. In such case make sure that you have the ofxGui addon.

Known issues
------------
-When wide lines overlap some artifacts might appear.

Version history
------------
First version.!

### Version 0.1 (08 JAN 2013): 


