#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup(){
	cur_drag=-1;
	tsize=0;
    size_of_AP=0;
    
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
    
    lineInit(4);
}
//--------------------------------------------------------------
void testApp::lineUpdate(){
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
void testApp::lineInit( int N)
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
	lineUpdate();
    tsize = size_of_AP; 
}
//--------------------------------------------------------------
ofxFatLineJointType testApp::getJointType()
{
	if ( jt_miter)
		return OFX_FATLINE_JOINT_MITER;
	else if ( jt_bevel)
		return OFX_FATLINE_JOINT_BEVEL;
	else if ( jt_round)
		return OFX_FATLINE_JOINT_ROUND;
	else
		return OFX_FATLINE_JOINT_MITER;
}
//--------------------------------------------------------------
ofxFatLineCapType testApp::getCapType()
{
	if ( jc_butt)
		return OFX_FATLINE_CAP_BUTT;
	else if ( jc_round)
		return OFX_FATLINE_CAP_ROUND;
	else if ( jc_square)
		return OFX_FATLINE_CAP_SQUARE;
	else if ( jc_rect)
		return OFX_FATLINE_CAP_RECT;
	else
		return OFX_FATLINE_CAP_BUTT;
}
//--------------------------------------------------------------
void testApp::enableCustomGLstates()
{
	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_COLOR_ARRAY);
    /*	
     glDisableClientState(GL_EDGE_FLAG_ARRAY);
     glDisableClientState(GL_FOG_COORD_ARRAY);
     glDisableClientState(GL_INDEX_ARRAY);
     glDisableClientState(GL_NORMAL_ARRAY);
     glDisableClientState(GL_SECONDARY_COLOR_ARRAY);
     glDisableClientState(GL_TEXTURE_COORD_ARRAY);
     //*/
}
//--------------------------------------------------------------
void testApp::disableCustomGLstates()
{
	glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_COLOR_ARRAY);
}

//--------------------------------------------------------------
void testApp::sliderChange(float & f){
    lineUpdate();
}
//--------------------------------------------------------------
void testApp::pointsChanged(int & n){
    lineInit(n);
}
//--------------------------------------------------------------
void testApp::buttonPressed(bool & b){
    lineUpdate();
}
//--------------------------------------------------------------
void testApp::update(){
    
}

//--------------------------------------------------------------
void testApp::draw(){
    ofBackground(255);
    ofFloatColor c (1,0,0,1);
    ofPushMatrix();
    ofPushView();
    glClearColor( 1.0,1.0,1.0,1.0f);
    glEnable(GL_BLEND);
    //glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	
	//glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	testDraw();
    
    
    ofPopView();
    ofPopMatrix();
    gui.draw();
    ofPushStyle();
    ofSetColor(0);
    ofDrawBitmapString(ofToString(ofGetFrameRate()), 100, ofGetHeight()-50);
    ofPopStyle();
}
//--------------------------------------------------------------
void testApp::testDraw(){
	enableCustomGLstates();
	
	ofxFatLineOptions opt;
	opt.feather    = feather;
	opt.feathering = feathering;
	opt.no_feather_at_cap = no_feather_at_cap;
	opt.no_feather_at_core = no_feather_at_core;
	opt.cap   = getCapType();
    opt.joint =getJointType();
	
	ofxFatLine(AP, AC, Aw,size_of_AP, &opt, triangulate);
	disableCustomGLstates();
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
    }
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
void testApp::windowResized(int w, int h){}
//--------------------------------------------------------------
void testApp::gotMessage(ofMessage msg){}
//--------------------------------------------------------------
void testApp::dragEvent(ofDragInfo dragInfo){}