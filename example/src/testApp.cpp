#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup(){
	curx=0; cury=0; lastx=0; lasty=0;
	cur_drag=-1;
	tsize=0;
    size_of_AP=0;
    
    bRedraw=true;
    
    gui.setup("panel");
    gui.add(start_weight.setup("start weight", 8, 0.02, 20));
    gui.add(weight.setup("weight", 8, 0.02, 200));
    gui.add(feathering.setup("feathering", 1, 1, 10));
    gui.add(feather.setup("feather", true));
    gui.add(no_feather_at_cap.setup("no feather at cap", false));
    gui.add(no_feather_at_core.setup("no feather at core", false));
    gui.add(jt_miter.setup("miter", true));
    gui.add(jt_bevel.setup("bevel", false));
    gui.add(jt_round.setup("round", false));
    gui.add(jc_butt.setup("butt", true));
    gui.add(jc_round.setup("round", false));
    gui.add(jc_square.setup("square", false));
    gui.add(jc_rect.setup("rect", false));
    gui.add(np.setup("Num Points", 3, 2, 6));

    gui.add(colored.setup("colored", true));
    gui.add(alphaed.setup("alphaed", true));
    gui.add(weighted.setup("weighted", false));
    gui.add(skeleton.setup("skeleton", false));
    gui.add( triangulate.setup("triangulation", false));
    
    weight.addListener(this, &testApp::sliderChange);
    feathering.addListener(this, &testApp::sliderChange);
    feather.addListener(this, &testApp::buttonPressed);
    no_feather_at_cap.addListener(this, &testApp::buttonPressed);
    no_feather_at_core.addListener(this, &testApp::buttonPressed);
    jt_miter.addListener(this, &testApp::buttonPressed);
    jt_bevel.addListener(this, &testApp::buttonPressed);
    jt_round.addListener(this, &testApp::buttonPressed);
    jc_butt.addListener(this, &testApp::buttonPressed);
    jc_round.addListener(this, &testApp::buttonPressed);
    jc_square.addListener(this, &testApp::buttonPressed);
    jc_rect.addListener(this, &testApp::buttonPressed);
    colored.addListener(this, &testApp::buttonPressed);
    alphaed.addListener(this, &testApp::buttonPressed);
    weighted.addListener(this, &testApp::buttonPressed);
    skeleton.addListener(this, &testApp::buttonPressed);
    triangulate.addListener(this, &testApp::buttonPressed);
    np.addListener(this, &testApp::pointsChanged);
        
    line_init(4);
}
//--------------------------------------------------------------
void testApp::line_update()
{
	ofFloatColor cc[3];
	ofFloatColor grey;
    grey.set(.4,.4,.4, 1);
	
    cc[0].set(1, 0, 0, 1);
    cc[1].set(0.8, 0.8, 0, 1);
    cc[2].set(0, 0, 1, 1);
	
	for ( int i=0; i<size_of_AP; i++){
		if (colored){
			AC[i] = cc[i%3];
        }else{
			AC[i] = grey;
        }
		if (alphaed){
			AC[i].a = 0.5f;
        }else{
			AC[i].a = 1.0f;
        }
		if (weighted){
			Aw[i] = weight * (0.05 + double(i*2)/size_of_AP);
		}else{
			Aw[i] = weight;
		}
	}
}
//--------------------------------------------------------------
void testApp::line_update_skeleton()
{
	ofFloatColor red;
    red.set(ofFloatColor::red);
	for ( int i=0; i<size_of_AP; i++){
		AC[i] = red;
		Aw[i] = 1.0;
	}
}
//--------------------------------------------------------------
void testApp::line_init( int N)
{
	switch (N)
	{
        case 2:
            AP[0].x=180; AP[0].y=270;
            AP[1].x=220; AP[1].y=30;
            size_of_AP = 2;
            break;
            
        case 3:
            AP[0].x=200; AP[0].y=100;
            AP[1].x=100; AP[1].y=200;
            AP[2].x=300; AP[2].y=200;
            size_of_AP = 3;
            break;
            
        case 4:
            AP[0].x=200; AP[0].y=50;
            AP[1].x=100; AP[1].y=150;
            AP[2].x=300; AP[2].y=150;
            AP[3].x=200; AP[3].y=250;
            size_of_AP = 4;
            break;
            
        case 5:
            AP[0].x=60; AP[0].y=250;
            AP[1].x=120; AP[1].y=50;
            AP[2].x=180; AP[2].y=250;
            AP[3].x=240; AP[3].y=50;
            AP[4].x=300; AP[4].y=250;
            size_of_AP = 5;
            break;
            
        case 6:
            AP[0].x=280; AP[0].y=110;
            AP[1].x=200; AP[1].y=50;
            AP[2].x=100; AP[2].y=150;
            AP[3].x=300; AP[3].y=150;
            AP[4].x=200; AP[4].y=250;
            AP[5].x=120; AP[5].y=190;
            size_of_AP = 6;
            break;
	}
	line_update();
    tsize = size_of_AP; 
}
//--------------------------------------------------------------
char testApp::get_joint_type()
{
	if ( jt_miter)
		return LJ_miter;
	else if ( jt_bevel)
		return LJ_bevel;
	else if ( jt_round)
		return LJ_round;
	else
		return 0;
}
//--------------------------------------------------------------
char testApp::get_cap_type()
{
	if ( jc_butt)
		return LC_butt;
	else if ( jc_round)
		return LC_round;
	else if ( jc_square)
		return LC_square;
	else if ( jc_rect)
		return LC_rect;
	else
		return 0;
}
//--------------------------------------------------------------
void testApp::drag_cb(){
    bRedraw = true;
}

//--------------------------------------------------------------
void testApp::enable_glstates()
{
	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_COLOR_ARRAY);
	
	glDisableClientState(GL_EDGE_FLAG_ARRAY);
	glDisableClientState(GL_FOG_COORD_ARRAY);
	glDisableClientState(GL_INDEX_ARRAY);
	glDisableClientState(GL_NORMAL_ARRAY);
	glDisableClientState(GL_SECONDARY_COLOR_ARRAY);
	glDisableClientState(GL_TEXTURE_COORD_ARRAY);
}
//--------------------------------------------------------------
void testApp::disable_glstates()
{
	glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_COLOR_ARRAY);
}

//--------------------------------------------------------------
void testApp::sliderChange(float & f){
    bRedraw = true;
    line_update();
}
//--------------------------------------------------------------
void testApp::pointsChanged(int & n){
    line_init(n);
	bRedraw = true;
    
}
//--------------------------------------------------------------
void testApp::buttonPressed(bool & b){
    bRedraw = true;
    line_update();
}
//--------------------------------------------------------------
void testApp::update(){

}

//--------------------------------------------------------------
void testApp::draw(){
    ofBackground(255);
    ofFloatColor c (1,0,0,1);
    if (bRedraw) {
        ofPushMatrix();
        ofPushView();
	//	glMatrixMode(GL_PROJECTION);
  //      glLoadIdentity();
       // glOrtho( 0, ofGetWidth(),ofGetHeight(),0,0.0f,100.0f);
        glClearColor( 1.0,1.0,1.0,1.0f);
//glClearDepth( 0.0f);
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	test_draw();
       // bRedraw = false;
}
    ofPopView();
    ofPopMatrix();
    gui.draw();
}
//--------------------------------------------------------------
void testApp::test_draw(){
	enable_glstates();
	
	polyline_opt opt={0};
	opt.feather    = feather;
	opt.feathering = feathering;
	opt.no_feather_at_cap = no_feather_at_cap;
	opt.no_feather_at_core = no_feather_at_core;
	opt.cap   = get_cap_type();
    opt.joint =get_joint_type();
	//float start_weight =0;
	for ( int i=0; i<20; i++)
	{
		ofVec2f  P1 (5+29.7*i, 187);
		ofVec2f  P2 (35+29.7*i, 8);
		Color C1 (0,0,0, 1);
		Color C2 = C1;
		double W1= 0.3*(i+1) + start_weight;
		double W2= W1;
		if ( colored)
		{
			Color cc1 ( 1.0,0.0,0.5, 1.0);
			C1 = cc1;
			Color cc2 ( 0.5,0.0,1.0, 1.0);
			C2 = cc2;
		}
		if ( alphaed)
		{
			C1.a = 0.5f;
			C2.a = 0.5f;
		}
		if ( weighted)
		{
			W1 = 0.1;
		}
		if ( opt.cap != LC_butt)
		{
			double end_weight = 0.3*(20) + start_weight;
			P1.y -= end_weight*0.5;
			P2.y += end_weight*0.5;
		}
		segment(P1, P2,       //coordinates
                C1, C2,       //colors
                W1, W2,       //weights
                &opt);        //extra options
	}
	
	for ( double ag=0, i=0; ag<2*PI-0.1; ag+=PI/12, i+=1)
	{
		double r1 = 0.0;
		double r2 = 90.0;
		if ( !weighted)
			r1 = 30.0;
		if ( opt.cap != LC_butt)
		{
			double end_weight = 0.3*(12) + start_weight;
			r2 -= end_weight*0.5;
		}
        
		
		double tx2=r2*cos(ag);
		double ty2=r2*sin(ag);
		double tx1=r1*cos(ag);
		double ty1=r1*sin(ag);
		double Ox = 120;
		double Oy = 194+97;
		
		ofVec2f  P1 (Ox+tx1,Oy-ty1);
		ofVec2f  P2 (Ox+tx2,Oy-ty2);
		Color C1 ( 0,0,0, 1);
		Color C2 = C1;
		double W1= 0.3*(i+1) + start_weight;
		double W2= W1;
		if ( colored)
		{
			Color cc1 ( 1.0,0.0,0.5, 1.0);
			C1 = cc1;
			Color cc2 ( 0.5,0.0,1.0, 1.0);
			C2 = cc2;
		}
		if ( alphaed)
		{
			C1.a = 0.5f;
			C2.a = 0.5f;
		}
		if ( weighted)
		{
			W1 = 0.1;
		}
		segment(P1, P2,       //coordinates
                C1, C2,       //colors
                W1, W2,       //weights
                &opt);        //extra options
	}
	polyline(AP, AC, Aw,size_of_AP, &opt, triangulate);
	disable_glstates();
}

//--------------------------------------------------------------
void testApp::keyPressed(int key){}
//--------------------------------------------------------------
void testApp::keyReleased(int key){}
//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y){}
//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button){
        if ( cur_drag >=0 && cur_drag< tsize){
            AP[cur_drag].x=x;
            AP[cur_drag].y=y;
            bRedraw = true;
        }
            lastx=x;
    lasty=y;
}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button){
	for ( int i=0; i<tsize; i++)
	{
		const short ALW=10;
		short dx=x-AP[i].x;
		short dy=y-AP[i].y;
		if ( -ALW<dx && dx<ALW)
            if ( -ALW<dy && dy<ALW)
            {
                cur_drag=i;
                return;
            }
	}
	cur_drag=-1;
}

//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button){}

//--------------------------------------------------------------
void testApp::windowResized(int w, int h){
    
}

//--------------------------------------------------------------
void testApp::gotMessage(ofMessage msg){
    
}

//--------------------------------------------------------------
void testApp::dragEvent(ofDragInfo dragInfo){ 
    
}