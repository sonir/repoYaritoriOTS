//
//  VSyn.cpp
//  vSyn
//
//  Created by sonir on 9/8/17.
//
//

#include "VSyn.hpp"

using namespace std;



//C++ Class

void VSyn::setup(){
    
  ofSetFrameRate(30);
    //// EventSetup ////
    
    //ResetFunction
    //SetUpEvents
//    auto f = [&](void* args){ //<- keep this desctiption
//        //draw your code
//        int *key_num = (int *)args;
//        //Reset State
//        agBuffReset(&gismo.agents);
//        agBuffReset(&gismo.add);
//        
//    };
//    gismo.lambdaAdd("/reset", f);
    
    
    ////////////////////
    
    //Set Metro
    metro = new Metro(GISMO_UPDATE_INTERVAL);
    
    ofBackground(255);
    ofSetCircleResolution(50);
    ofSetFrameRate(30);
    screen_w = ofGetWidth();
    screen_h = ofGetHeight();

    //CAM SETUP
    cam_flg = false;
    pov.set(POV_INIT_X*ofGetWidth()*(-1), POV_INIT_Y*ofGetHeight(), POV_INIT_Z*ofGetWidth());
    look.set(LOOK_INIT_X*ofGetWidth()*(-1), LOOK_INIT_Y*ofGetHeight(), LOOK_INIT_Z*ofGetWidth());
    //Setup Particles
    particle.setup(ofGetWidth(),ofGetHeight());
    
    cout << "VSyn SETUP" << endl;
    receiver.setup(PORT);    
    current_msg_string = 0;
    
    //Init Buffers for Graphics
    initColors(CONTAINER_MAX);
    initShapes(CONTAINER_MAX);
    
    //Setup Gismo
    gismo.setup();
    //SetupEvents
    gismo.eventAdd("/addAgentWithShape", this);
    
    //Set events
    gismo.eventAdd("/ripple", &ripple);
    gismo.eventAdd("/solo", &visual.events.solo);
    
    //Set ag_shape_t and gismo pointer
    visual.motion.setShapePtr(ag_shapes);
    visual.events.setMotionManagerPtr(&visual.motion);
    ripple.setMotionManagerPtr(&visual.motion);
    
    //Set window size for yaritori
#ifdef DEBUG_MODE
    ofSetWindowShape(DISPLAY_WIDTH, DISPLAY_HEIGHT);
    renderer.setup(DISPLAY_WIDTH, DISPLAY_HEIGHT);
#else
    scManager.setup();
    renderer.setup(BASE_HEIGHT, BASE_HEIGHT);
    renderer.setCircleBaseRad(DISPLAY_WIDTH);
#endif
    
    //Color settings
#ifdef DEBUG_MODE
    renderer.setColor(1.0);
    ripple.setColor(1.0);
    ofBackground(0);
#else
    scManager.setBackground(BACKGROUND_COLOR_DEFAULT);
    visual.motion.setColor(ANIMATION_COLOR_DEFAULT);
    renderer.setColor(ANIMATION_COLOR_DEFAULT);
    ripple.setColor(ANIMATION_COLOR_DEFAULT);
#endif
    
    //Create TestClass
    myTest = new Test();
    myTest->setup();

    //Init agent
    agBuffReset(&gismo.agents);
    agBuffReset(&gismo.add);

    //Do Test Code
    //this->test();
    
    myTest->setup();
    //Do Test Code
//    this->test();
    
    
    //Load Previous Agents
    int inum = 1;
    gismo.bang("/yaritori/load" , &inum);
//    csv2buffter.createAgents(gismo.add.buf, "0-agents.csv");


    scManager.setFullScreen();
}


void VSyn::update(){
    
    
//    cout << frand() << endl;
    
#ifdef DEBUG_MODE
    cout << "######### ag=" << gismo.agents.count << endl;
    
    for(int i=0;i<gismo.agents.count; i++){
     
        ag_t *ag = gismo.getAgent(i);
        cout << ag->agid << " , " << ag->size << endl;
    }
        
    cout << "---" << endl;
    for(int i=0;i<ag_shapes_count; i++){
        
        
        cout << ag_shapes[i].color << " , " << ag_shapes[i].node_count << endl;
        
        
    }
#endif
   
    
    //Test Update
    myTest->update();
//    if( !sound.bankIsEmpty()) sound.update();
        
    
    //sync();

    gismo.addSync();
    if(metro->update())makeInteracts(&gismo.agents);
    //makeInteracts(&gismo.agents);
    
    // hide old messages
    for(int i = 0; i < NUM_MSG_STRINGS; i++){
        if(timers[i] < ofGetElapsedTimef()){
            msg_strings[i] = "";
        }
    }
    
    // check for waiting messages
    while(receiver.hasWaitingMessages()){
        // get the next message
        ofxOscMessage m;
        receiver.getNextMessage(m);
        
        // check for mouse moved message
        if(m.getAddress() == "/circle"){
            
            int uid =  m.getArgAsInt32(0);
            float x = m.getArgAsFloat(1);
            float y = m.getArgAsFloat(2);
            float size = m.getArgAsFloat(3);
            int fill = m.getArgAsInt32(4);
            
            if(uid < CONTAINER_MAX) // check the index is enable
            {
                toCircle(&shapes[uid] ,uid, x, y, size, fill);
            }
        } else if(m.getAddress() == "/triangle"){
            
            int uid =  m.getArgAsInt32(0);
            float x = m.getArgAsFloat(1);
            float y = m.getArgAsFloat(2);
            float size = m.getArgAsFloat(3);
            float angle = m.getArgAsFloat(4);
            int fill = m.getArgAsInt32(5);
            
            if(uid < CONTAINER_MAX) // check the index is enable
            {
                toTriangle(&shapes[uid] ,uid, x, y, size, angle, fill);
            }
        } else if(m.getAddress() == "/square"){
            
            int uid =  m.getArgAsInt32(0);
            float x = m.getArgAsFloat(1);
            float y = m.getArgAsFloat(2);
            float size = m.getArgAsFloat(3);
            float angle = m.getArgAsFloat(4);
            int fill = m.getArgAsInt32(5);
            
            if(uid < CONTAINER_MAX) // check the index is enable
            {
                toSquare(&shapes[uid] ,uid, x, y, size, angle, fill);
            }
        } else if(m.getAddress() == "/rect"){
            
            int uid =  m.getArgAsInt32(0);
            float x1 = m.getArgAsFloat(1);
            float y1 = m.getArgAsFloat(2);
            float x2 = m.getArgAsFloat(3);
            float y2 = m.getArgAsFloat(4);
            float angle = m.getArgAsFloat(5);
            int fill = m.getArgAsInt32(6);
            
            if(uid < CONTAINER_MAX) // check the index is enable
            {
                toRect(&shapes[uid] ,uid, x1, y1, x2, y2, angle, fill);
            }
        } else if(m.getAddress() == "/line"){
            
            int uid =  m.getArgAsInt32(0);
            float x1 = m.getArgAsFloat(1);
            float y1 = m.getArgAsFloat(2);
            float x2 = m.getArgAsFloat(3);
            float y2 = m.getArgAsFloat(4);
            float thick = m.getArgAsFloat(5);
            
            if(uid < CONTAINER_MAX) // check the index is enable
            {
                toLine(&shapes[uid] ,uid, x1, y1, x2, y2, thick);
            }
        } else if(m.getAddress() == "/arc"){
            
            int uid =  m.getArgAsInt32(0);
            float x1 = m.getArgAsFloat(1);
            float y1 = m.getArgAsFloat(2);
            float x2 = m.getArgAsFloat(3);
            float y2 = m.getArgAsFloat(4);
            float height = m.getArgAsFloat(5);
            float expose = m.getArgAsFloat(6);
            float thick = m.getArgAsFloat(7);
            
            if(uid < CONTAINER_MAX) // check the index is enable
            {
                toArc(&shapes[uid] ,uid, x1, y1, x2, y2, height, expose, thick);
            }
        } else if(m.getAddress() == "/wave"){
            
            int uid =  m.getArgAsInt32(0);
            
            float x1 = m.getArgAsFloat(1);
            float y1 = m.getArgAsFloat(2);
            float x2 = m.getArgAsFloat(3);
            float y2 = m.getArgAsFloat(4);
            float freq = m.getArgAsFloat(5);
            float amp = m.getArgAsFloat(6);
            float phase = m.getArgAsFloat(7);
            float thick = m.getArgAsFloat(8);
            
            if(uid < CONTAINER_MAX) // check the index is enable
            {
                toWave(&shapes[uid] ,uid, x1, y1, x2, y2, freq, amp, phase, thick);
            }
            
        } else if(m.getAddress() == "/color"){
            
            int uid = m.getArgAsInt32(0);
            if(uid < CONTAINER_MAX) // check the index is enable
            {
                colors[uid].r = (char) ( 255.0f * m.getArgAsFloat(1) );
                colors[uid].g = (char) ( 255.0f * m.getArgAsFloat(2) );
                colors[uid].b = (char) ( 255.0f * m.getArgAsFloat(3) );
                colors[uid].a = (char) ( 255.0f * m.getArgAsFloat(4) );
                
            }

        } else if(m.getAddress() == "/mute"){
            
            int uid =  m.getArgAsInt32(0);
            bool flg = (bool)m.getArgAsInt32(1);

            
            if(uid < CONTAINER_MAX) // check the index is enable
            {
                toMute(&shapes[uid], flg);
            }
            
        } else if(m.getAddress() == "/cam/pov"){
            
            pov.x =  ( m.getArgAsFloat(0) * ofGetWidth() * (-1)); //Invert x posi for GL coordinate sys
            pov.y =  ( m.getArgAsFloat(1) * ofGetWidth() );
            pov.z =  ( m.getArgAsFloat(2) * ofGetWidth() );
            
        } else if(m.getAddress() == "/cam/look"){
            
            look.x =  ( m.getArgAsFloat(0) * ofGetWidth()  * (-1) ); //Invert x posi for GL coordinate sys
            look.y =  ( m.getArgAsFloat(1) * ofGetWidth() );
            look.z =  ( m.getArgAsFloat(2) * ofGetWidth() );
            
        } else if(m.getAddress() == "/cam/on"){
            
            if ( m.getArgAsInt(0) == 1 )
                cam_flg = true;
            else if(m.getArgAsInt(0) == 0)
                cam_flg = false;
            
        }else if(m.getAddress() == "/particle/attractor/x"){
            
            particle.attractor_x = m.getArgAsFloat(0) * ofGetWidth();
            
        }else if(m.getAddress() == "/particle/attractor/y"){
            
            particle.attractor_y = m.getArgAsFloat(0) * ofGetHeight();
            
        }else if(m.getAddress() == "/particle/modulation"){
            
            particle.modulation = m.getArgAsFloat(0);
            
        }else if(m.getAddress() == "/particle/size"){
            
            particle.size = m.getArgAsFloat(0) * 2.5;
            
        }else if(m.getAddress() == "/particle/num"){
            
            particle.particleNum = m.getArgAsInt(0);
            
        }else if(m.getAddress() == "/particle/mode"){
            
            //particle.mode = m.getArgAsInt(0);
            int flg =  m.getArgAsInt(0);
            switch (flg){
                    
                case 0:
                    particle.mode = BROWNIAN;
                    break;
                case 1:
                    particle.mode = GRAVITY;
                    break;
                case 2:
                    particle.mode = GATHERING;
                    break;
                    
                    
            }
            
        }else {
            
            cout << "OSC :: unknown ADR :: " << m.getAddress() << endl;
            
        }
        
        
   
    }// end of while

    
    particle.update();

}


void VSyn::initColors(int max_num){
    
    for(int i=0; i<max_num; i++){
        
        colors[i].r = 255;
        colors[i].g = 255;
        colors[i].b = 255;
        colors[i].a = 255;
        
        
    }
    
}


void VSyn::initShapes(int max_num){

    for(int i=0; i<max_num; i++){

        shapeContainer *pC = &shapes[i];
        pC->type = VOID;
        pC->active = true;
        pC->uid = -1;
        
        pC->x1 = 0.5f;
        pC->y1 = 0.5f;
        pC->x2 = 0.5f;
        pC->y2 = 0.5f;
        
        pC->size = 0.0f;
        pC->height = 0.0f;
        pC->angle = 0.0f;
        pC->freq = 0.0f;
        pC->amp = 0.0f;
        pC->phase = 0.0f;
        pC->thick = 0.0f;
        pC->expose = 1.0f;
        
        pC->fill = false;

        
    }

}



void VSyn::draw(){
    
    screen_w = ofGetWidth();
    screen_h = ofGetHeight();

    
    //CAM CONTROL
    if(cam_flg){
        
        cam.begin();
        cam.setPosition(pov);
        cam.lookAt(look);
        
        //Invert Y axis for GL
        ofPushMatrix();
        ofScale(1, -1); //Invert Y only
        
    }


    //drawing particle
    particle.draw();
    
#ifdef DEBUG_MODE
    //drawAgentsForSimpleGraphics for debugging
    drawAgentsWithChar.draw(&gismo, screen_w, screen_h);
    
    
    performanceManager.updateLines();
    performanceManager.updateLinesInverted();
    
    if(performanceManager.mode == PHASE1_AG_SLAVE || performanceManager.mode == PHASE1_AG_MASTER){
        drawPerformance(&performanceManager);
    }
    
    renderer.draw();
    
    
#else
    //drawAgents
    scManager.begin();
    
    //Draw Agents normally
    drawAgents(&visual);
    
    //Ripple
    ripple.draw();
    
//    ofSetColor(scManager.getDrawColor());

    performanceManager.updateLines();
    performanceManager.updateLinesInverted();
    if(!visual.motion.isSoloMode()) {
        if(performanceManager.mode == PHASE1_AG_SLAVE || performanceManager.mode == PHASE1_AG_MASTER){
            drawPerformance(&performanceManager);
        }
        
        renderer.draw();
    }
    
    scManager.end();
    scManager.draw();
#endif
    
    
    for(int i=0; i<CONTAINER_MAX; i++){
        
        shapeContainer *elm = &shapes[i];
        //Set Color
        ofSetColor(colors[i]);

        if ( !elm->active || elm->type == VOID){
            
            continue;
            
        }
        
        switch(elm->type){
                
            case CIRCLE:
                circle(elm->x1, elm->y1, elm->size, elm->fill);
                break;
                
            case TRIANGLE:
                triangle(elm->x1, elm->y1, elm->size, elm->angle, elm->fill);
                break;

            case SQUARE:
                square(elm->x1, elm->y1, elm->size, elm->angle, elm->fill);
                break;

            case RECT:
                rect(elm->x1, elm->y1, elm->x2, elm->y2, elm->angle, elm->fill);
                break;

            case LINE:
                line(elm->x1, elm->y1, elm->x2, elm->y2, elm->thick);
                break;

            case ARC:
                arc(elm->x1, elm->y1, elm->x2, elm->y2, elm->height, elm->expose, elm->thick);
                break;

            case WAVE:
                wave(elm->x1, elm->y1, elm->x2, elm->y2, elm->freq, elm->amp, elm->phase, elm->thick);
                break;
                
            default:
                break;
                
        }
    }


    //Draw Performers
    /*
    for(int i=0; i<PERFORMER_NUM;i++){
        
        circle(performance.performers.pfm.buf[i].posi.x, performance.performers.pfm.buf[i].posi.x, SIZE_OF_PERFORMER_INDICATE,false);
        
    }
    
    for(int i=0; i< gismo.agents.count;i++){
        
        line_t *tmp = &performance.lines[i];
        tmp->node_a.x = gismo.agents.buf[i].posi.x;
        tmp->node_a.y = gismo.agents.buf[i].posi.y;
        tmp->node_b.x = performance.performers.pfm.buf[i%PERFORMER_NUM].posi.x;
        tmp->node_b.y = performance.performers.pfm.buf[i%PERFORMER_NUM].posi.y;
        
        line(tmp->node_a.x, tmp->node_a.y, tmp->node_b.x , tmp->node_b.y, 0.1f);
        //tmp->points[0].bang();
        //cout << tmp->points[0].update() << endl;;
        
        performance.bullets[i].bang();
        posi_t pos = performance.bullets[i].update(performance.lines[i]);
        circle(pos.x, pos.y, 0.0045, 1);

        
    }
    
    //bullet->bang();
    posi_t tmp = bullet->update(aLine);
    circle(tmp.x, tmp.y, 0.0045, 1);
    cout << tmp.x << endl;
     */

    
    if(cam_flg){
        ofPopMatrix();
        cam.end();
    }
    
}

void VSyn::keyPressed(int key) {
    switch (key) {
        case 'y':
            scManager.setFullScreen();
            break;
        case 'e':
            ofExit();
            break;
        default:
            break;
    }
}

void VSyn::initWindowSize(){
    
    int tmp_w = ofGetWidth();
    int tmp_h = ofGetHeight();
    
    initCanvasSize(tmp_w, tmp_h);
    particle.screen_width = tmp_w;
    particle.screen_height = tmp_h;

}


void VSyn::addAgShape(ag_shape_t shape){
    
    //Count exceeding check
    if( ag_shapes_count >= AG_MAX ){
        
        ag_shapes_count = 0;
        
    }
    
    ag_shapes[ag_shapes_count] = shape;
    ag_shapes_count += 1;
    
    

    
}


void VSyn::test(){

    //Draw Your Test Code. This method was invoked when the end of setup().
    std::cout << "test method is starting..." << std::endl;
    
    //Run test codes
    myTest->run();
    myTest->runVisualTest(&visual);
    

    //Test addAgShape
    ag_shape_t shape;

    shape.nodes[0].x = -0.5f;
    shape.nodes[0].y = 0.5f;
    shape.nodes[1].x = 0.5f;
    shape.nodes[1].y = 0.5f;
    shape.nodes[2].x = 0.5f;
    shape.nodes[2].y = -0.5f;
    shape.nodes[3].x = -0.5f;
    shape.nodes[3].y = -0.5f;
    shape.node_count = 4;
    shape.edges[0].node_id_a = 0;
    shape.edges[0].node_id_b = 1;
    shape.edge_count = 1;
    for(int i=0;i < AG_MAX;i++) { 
        ag_shapes[i] = shape;
        //gismo.bang("/addShape", &shape);
    }
    assert(ag_shapes_count == 0);
    
    
    //assert(ag_shapes_count == 1);
    //assert( ag_shapes[0].node_count == 2 );
    //assert (ag_shapes[0].edges[0].node_id_b == 1);
    std::cout << "VSyn:: addAgShape is ok." << std::endl;

    
    //Test Where am I
    region_e where;
    //float width = gismo.width_rate;
    float width = 1.5;
    posi_t posi;
    posi.x = 0.49f;
    posi.y = 0.5f;
    where = whereAmI(posi, width);
    assert(where == REGION_LEFT);
    posi.x = 0.5f;
    where = whereAmI(posi, width);
    assert(where == REGION_CENTER);
    posi.x = 1.0f;
    where = whereAmI(posi, width);
    assert(where == REGION_RIGHT);
    cout << "VSyn :: CFunc :: whereAmI is OK." << endl;
    

    //Test BUFFER2CSV::Agents
    ag_t agsOrg[4];
    agsOrg[0].agid = 0;
    agsOrg[0].active = true;
    agsOrg[0].posi.x = 0.001f;
    agsOrg[0].posi.y = 0.01f;
    agsOrg[0].size = 0.1f;
    agsOrg[0].view = 1.1f;
    agsOrg[0].mov = 11.1f;
    agsOrg[0].condition = (condition_e)0;
    agsOrg[0].spd.x = 111.1f;
    agsOrg[0].spd.y = 111.1f;
    agsOrg[0].interact_with = 110;

    agsOrg[1].agid = 1;
    agsOrg[1].active = true;
    agsOrg[1].posi.x = 0.002f;
    agsOrg[1].posi.y = 0.02f;
    agsOrg[1].size = 0.2f;
    agsOrg[1].view = 2.2f;
    agsOrg[1].mov = 22.2f;
    agsOrg[1].condition = (condition_e)1;
    agsOrg[1].spd.x = 222.2;
    agsOrg[1].spd.y = 2222.2;
    agsOrg[1].interact_with = 220;
    
    agsOrg[2].agid = 2;
    agsOrg[2].active = false;
    agsOrg[2].posi.x = 0.003f;
    agsOrg[2].posi.y = 0.03f;
    agsOrg[2].size = 0.3f;
    agsOrg[2].view = 3.3f;
    agsOrg[2].mov = 33.3f;
    agsOrg[2].condition = (condition_e)RUN;
    agsOrg[2].spd.x = 333.3;
    agsOrg[2].spd.y = 3333.3;
    agsOrg[2].interact_with = 330;
    
    //Test addAgShape
//    ag_shape_t shape;
//    shape.node_count = 2;     //137
//    shape.edges[1].node_id_a = 50; //138
//    gismo.bang("/addShape" , &shape);
//    addAgShape(shape); //Add the shape
//    assert(ag_shapes_count == 1);
//    assert( ag_shapes[0].node_count == 2 );
//    assert (ag_shapes[0].edges[1].node_id_a == 50);
//    std::cout << "VSyn:: addAgShape is ok." << std::endl;

    //Test CSV2BUFFER::Agents
    ag_t ags[4];
    csv2buffer.loadAgents(ags, "test.csv");
    assert(ags[0].agid == 0);
    assert(ags[0].size == 0.1f);
    assert(ags[1].agid == 1);
    assert(ags[1].view == 2.2f);
    assert(ags[2].agid == 2);
    assert(ags[2].active == false);
    assert(ags[2].posi.x == 0.003f);
    assert(ags[2].posi.y == 0.03f);
    assert(ags[2].size == 0.3f);
    assert(ags[2].view == 3.3f);
    assert(ags[2].mov == 33.3f);
    assert(ags[2].condition == RUN);
    cout << ags[2].spd.x << endl;
    assert(ags[2].spd.x == 333.3f);
    assert(ags[2].spd.y == 3333.3f);
    assert(ags[2].interact_with == 330);
    cout << "CSV to Buffer is OK" << endl;
    
    
    //Reset at Once
    int val = 1;
    gismo.bang("/gismo/reset" , &val);

    //Test CSV2BUFFER::Shapes
    csv2buffer.loadShapes("test_shape.csv");
    assert( ag_shapes[0].color == 0.1f);
    assert( ag_shapes[1].color == 0.2f);
    assert( ag_shapes[2].color == 0.3f);
    assert( ag_shapes[0].node_count==4 && ag_shapes[0].edge_count == 1 );
    assert( ag_shapes[1].node_count==4 && ag_shapes[1].edge_count == 2 );
    assert( ag_shapes[0].nodes[1].x == 0.5f);
    assert( ag_shapes[0].nodes[1].y == -0.5f);
    assert( ag_shapes[1].edges[1].node_id_a==1 );
    assert( ag_shapes[1].edges[1].node_id_b==3 );

//    createShape(shape);
//    gismo.bang("/addShape" , &shape);
//    createShape(shape);
//    gismo.bang("/addShape" , &shape);

//    for(int i = 0; i < AG_MAX; i++) {
//        createShape(shape);
//        gismo.bang("/addShape" , &shape);
//    }
    
    //Test BUFFER2CSV::Shapes
    buffer2csv.saveShapes(ag_shapes, 3, "test_shape.csv");
    //LoadTestOnceMore
    csv2buffer.loadShapes("test_shape.csv");
    assert( ag_shapes[0].color == 0.1f);
    assert( ag_shapes[1].color == 0.2f);
    assert( ag_shapes[2].color == 0.3f);
    assert( ag_shapes[0].node_count==4 && ag_shapes[0].edge_count == 1 );
    assert( ag_shapes[1].node_count==4 && ag_shapes[1].edge_count == 2 );
    assert( ag_shapes[0].nodes[1].x == 0.5f);
    assert( ag_shapes[0].nodes[1].y == -0.5f);
    assert( ag_shapes[1].edges[1].node_id_a==1 );
    assert( ag_shapes[1].edges[1].node_id_b==3 );
     

    //Test SOUND_LOAD
    sound_t testSounds[3];
    testSounds[0].genre=11;
    testSounds[0].song=12;
    testSounds[0].slice=13;
    testSounds[0].effect_val=1.4;
    testSounds[0].region=(region_e)15;
    
    
    testSounds[1].genre=21;
    testSounds[1].song=22;
    testSounds[1].slice=23;
    testSounds[1].effect_val=2.4;
    
    
    testSounds[2].genre=31;
    testSounds[2].song=32;
    testSounds[2].slice=33;
    testSounds[2].effect_val=3.4;
    
    
    testSounds[1].region=(region_e)25;
    testSounds[2].region=(region_e)35;
    buffer2csv.saveSounds(testSounds, 3, "test_sound.csv");
    //CSV2BUFFER :: SOUND
    csv2buffer.loadSounds("test_sound.csv");
    
    //cout << soundTrigger.sounds[0].genre << endl;
    assert(soundTrigger.sounds[0].genre == 11);
    assert(soundTrigger.sounds[1].genre == 21);
    assert(soundTrigger.sounds[2].genre == 31);
    assert(soundTrigger.sounds[0].song == 12);
    assert(soundTrigger.sounds[1].song == 22);
    assert(soundTrigger.sounds[2].song == 32); //<<
    assert(soundTrigger.sounds[0].slice == 13);
    assert(soundTrigger.sounds[1].slice == 23);
    assert(soundTrigger.sounds[2].slice == 33);
    assert(soundTrigger.sounds[0].effect_val == 1.4f);
    assert(soundTrigger.sounds[1].effect_val == 2.4f);
    assert(soundTrigger.sounds[2].effect_val == 3.4f);
    assert((int)soundTrigger.sounds[0].region == 15);
    assert((int)soundTrigger.sounds[1].region == 25);
    assert((int)soundTrigger.sounds[2].region == 35);
    
    cout << soundTrigger.sounds[0].song << endl;
    cout << soundTrigger.sounds[1].song << endl;
    cout << soundTrigger.sounds[2].song << endl;

    
    
    
    
    //Reset all agents
    int num=1;
    gismo.bang("/gismo/reset" , &num);

//    agBuffReset(&gismo.agents);
//    agBuffReset(&gismo.add);
    
    //Set Agents
    ag_t ag;



    
    initAgentActive(&ag);
    ag.posi.x = 0.25f; ag.posi.y = 0.5f;
    //gismo.addAgent(ag);
    ag.posi.x = 0.75f; ag.posi.y = 0.5f;
    

    //Add TestAgent A
    for(int i=0;i<DUMMY_AG_A_NUM;i++) gismo.addAgent(ag);

    //Add TestAgentB
    //Change param for AgentB
    ag.size *= 0.8f;
    ag.mov *= 2.5f;
    ag.view *= 1.0f;
    for(int i=0;i<DUMMY_AG_B_NUM;i++) gismo.addAgent(ag);
    
    
    
    
    std::cout << "test method has finished." << std::endl;
    //Reset State
    agBuffReset(&gismo.agents);
    agBuffReset(&gismo.add);


    
}
