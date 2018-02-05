//
//  Test.cpp
//  yaritori
//
//  Created by sonir on 12/27/17.
//
//

#include "Test.hpp"

Test :: Test(){
//    sound = pSnd;
//    ripple = pRipple;
}


void Test :: setup(){
    
    //Making lambda event
    auto f = [&](void* args){
        
        //draw your own process for your event
        int *foo = (int *)args;
        runSubTest(args); //you can invoke other function in your event
        
    };
    gismo.lambdaAdd("/lambdaTest", f);

    
}

void Test :: runSubTest(void* args){
    
    param_u *params = (param_u *)args;
    arg1 = params[0].ival;
    arg2 = params[1].ival;
    cout << "---" << endl;
    cout << "EVENT /lambdaTest arg1=" << arg1 << endl;
    cout << "EVENT /lambdaTest arg2=" << arg2 << endl;
    cout << "---" << endl;
    
}


void Test :: run(){
    
    
    //Test frand
//    assert( frand()==0.1f );
//    assert( frand()==0.7f );
//    assert( frand()==0.7f );
//    assert( frand()==0.1f );
//    cout << "gismoManager::randmom() is OK."<<endl;
    

    cout << "CLASS Sound is ok.(check the receive yourself.)" << endl;

    
    //TestEventHandler
    EventHandler eventHandler;
    EvTest evTest;
    eventHandler.eventAdd("/t01" , &evTest);
    int args[] = {0,1,2};
    assert ( eventHandler.bang("/t01", args) == 138 );
    assert ( eventHandler.bang("/t01") == 137 );
    cout << "GismoBundledClass::eventHandler is OK." << endl;
    //Test EventHandler with Gismo
    gismo.eventAdd("/t01" , &evTest);
    assert ( gismo.bang("/t01" , args) == 138 );
    //Sound Trigger
    int snd_id = 0;
    setSound(0);
    setSound(2);
    setSound(4);
    cout << "GismoManager::eventHandler with Gismo is OK." << endl;
    
    
    
    //Define an agent
    ag_t ag;
    
    //Test GismoManager.getAgents()
    ag_t *agents = gismo.getAgents();
    agents[0].posi.x = 0.13f;
    agents[0].posi.y = 0.2f;
    assert(agents[0].posi.x == 0.13f);
    assert(agents[0].posi.y == 0.2f);
    cout << "GismoManager:getAgent() is OK." << endl;
    
    //Test GismoLibrary distance()
    posi_t tmp1, tmp2;
    tmp1.x = 0.0f;
    tmp1.y = 0.0f;
    tmp2.x = 3.0f;
    tmp2.y = 4.0f;
    assert(distance(tmp1, tmp2) == 5.0f);
    tmp1.x = 0.5f;
    tmp1.y = 0.5f;
    tmp2.x = -0.5f;
    tmp2.y = -0.5f;
    assert(distance(tmp1, tmp2)==(float)sqrt(2.0f));
    tmp1.x = 3.0f;
    tmp1.y = 4.0f;
    tmp2.x = 0.0f;
    tmp2.y = 0.0f;
    assert(distance(tmp1, tmp2) == 5.0f);
    tmp1.x = 5.0f;
    tmp1.y = 12.0f;
    tmp2.x = 0.0f;
    tmp2.y = 0.0f;
    assert(distance(tmp1, tmp2) == 13.0f);
    cout << "GismoLibrary:distance() is OK." << endl;
    
    
    //Test Init AgentActive
    initAgentActive(&ag);
    assert(ag.size == AG_DEF_SIZE);
    assert(ag.active==true);
    cout << "GismoLibrary:initAgentActive() is OK." << endl;
    
    //TestAgentAdd
    initAgentActive(&ag);
    ag.view = 0.23f;
    ag.posi.x = 0.2f; ag.posi.y=0.2f;
    gismo.addAgent(ag);
    assert (gismo.add.buf[0].view == 0.23f);
    assert (gismo.add.count == 1);
    cout << "GismoManager:addAgent() is OK." << endl;
    
    //TestSync
    ag_t ag2;
    initAgentActive(&ag2);
    ag2.view = 0.34f;
    gismo.addAgent(ag2);
    gismo.addSync(); //Finally gismo requires sync to avoid direct agent addition when processing agents.
    assert(gismo.add.count==0 && gismo.agents.count==2);
    assert(agents[0].active && agents[1].active);
    assert(agents[0].view==0.23f && agents[1].view==0.34f);
    cout << "gismoLibrary:addSync() is OK." << endl;
    
    //Test gismo Library seekNearest();
    agents[0].posi.x = 0.0f;
    agents[0].posi.y = 0.0f;
    agents[1].posi.x = 0.5f;
    agents[1].posi.y = 0.5f;
    ag_t ag3;
    initAgentActive(&ag3);
    ag3.posi.x = 0.5f;
    ag3.posi.y = 0.49f;
    gismo.addAgent(ag3); //add the new agent to addBuffer
    ag_t ag4;
    ag4.posi.x = 0.7f;
    ag4.posi.y = 0.49f;
    gismo.addAgent(ag3); //add the new agent to addBuffer
    gismo.addSync(); //refrect the add buffer to actual buffer
    int nearest_agent = seekNearest(0, &gismo.agents); //seek the nearest agent of agent[0]
    cout << nearest_agent << endl;
    assert(nearest_agent==2);
    cout << "gismoManager:seekNearest() is OK."<<endl;
    
    
    //Test isViewRange
    /* REST FOR  VIEW/MOV  RATE
    ag_t ag5;
    ag5.view = 0.5f;
    assert( isViewRange(&ag5,0.3f)==true );
    assert( isViewRange(&ag5,0.51f)==false );
    cout << "gismoLibrary::isViewRange() is OK" << endl;
    
    //Test isLarge
    assert( isLarge(0.5 , 0.4)==true );
    assert( isLarge(0.5, 0.501)==false);
    cout << "gismoLibrary::isaLarge is OK" <<endl;

     
    //Test Move
    ag_t ag6;
    posi_t tmp;
    tmp.x=1.0; tmp.y=0.0;
    initAgent(&ag6);
    ag6.posi.x=0.5; ag6.posi.y=0.5;
    move(&ag6,&tmp);
    assert(ag6.posi.x >= 0.5f);
    assert(ag6.posi.y <= 0.5f);
    cout << "gismoLibrary::move() is OK." << endl;
    
    //Test Run
    ag_t tmpAg1, tmpAg2;
    tmpAg1.posi.x = 0.75f;
    tmpAg1.posi.y = 0.75f;
    tmpAg1.mov = 0.001f;
    tmpAg1.spd.x = 0.0f;
    tmpAg1.spd.y = 0.0f;
    tmpAg2.posi.x = 0.5f;
    tmpAg2.posi.y = 0.5f;
    running(&tmpAg1, &tmpAg2.posi);
    assert(tmpAg1.posi.x >= 0.75f);
    assert(tmpAg1.posi.y >= 0.75f);
    tmpAg1.posi.x = 0.25f;
    tmpAg1.posi.y = 0.75f;
    tmpAg1.spd.x = 0.0f;
    tmpAg1.spd.y = 0.0f;
    running(&tmpAg1, &tmpAg2.posi);
    assert(tmpAg1.posi.x <= 0.25f);
    assert(tmpAg1.posi.y >= 0.75f);
    tmpAg1.posi.x = 0.75f;
    tmpAg1.posi.y = 0.45f;
    tmpAg1.spd.x = 0.0f;
    tmpAg1.spd.y = 0.0f;
    running(&tmpAg1, &tmpAg2.posi);
    assert(tmpAg1.posi.x >= 0.75f);
    assert(tmpAg1.posi.y <= 0.45f);
    tmpAg1.posi.x = 0.25f;
    tmpAg1.posi.y = 0.25f;
    tmpAg1.spd.x = 0.0f;
    tmpAg1.spd.y = 0.0f;    
    running(&tmpAg1, &tmpAg2.posi);
    //0115 assert(tmpAg1.posi.x < 0.25f);
    //assert(tmpAg1.posi.y < 0.25f);
    cout << "gismoLibrary::running() is OK." << endl;
    
    //TestConditionCheck
    condition_e cond1 = CALM;
    condition_e cond2 = RUN;
    assert ( conditionCheck(cond1, cond2) == false );
    cond2 = CALM;
    assert ( conditionCheck(cond1, cond2) == true );
    
    //Test interactWith()
    ag_t ag8 , ag9;
    initAgent(&ag8);
    initAgent(&ag9);
    ag8.size = 1.0f;
    ag8.posi.x = 0.0f; ag8.posi.y = 0.0f;
    ag9.posi.x = 1.0f; ag9.posi.y = 1.0f;
    ag8.view = 1.5;
    interactWith(&ag8 , &ag9);
    */
    
    //TestReset
    agents[0].active=true;
    agents[1].active=true;
    agBuffReset(&gismo.agents);
    assert(agents[0].active==false);
    assert(agents[1].active==false);
    assert(gismo.agents.count == 0);
    
    
    //TestLogistic
    float fval=0.5;
    fval = logistic(fval);
    assert(fval==0.75f);
    fval = logistic(fval);
    cout << "GismoLibrary::logistic() is OK." << endl;        

    //Test
    //agBuffReset(&gismo.agents);
    int val = 1;
    gismo.bang("/gismo/reset" , &val);
    ag_t ag1;
    initAgent(&ag1);
    ag1.view = 256.0f;
    gismo.agents.buf[0] = ag1;
    ag1.view = 356.0f;
    gismo.agents.buf[1] = ag1;
    ag_t *pAg1 = gismo.getAgent(0);
    assert(pAg1->view == 256.0f);
    ag_t *pAg2 = gismo.getAgent(1);
    assert(pAg2->view == 356.0f);
    
    //TestSpeedLimit
    assert ( limitter(1.1f, 1.0f) == 1.0f );
    assert ( limitter(-1.1f, 1.0f) == -1.0f );
    assert ( limitter(0.49f, 0.5f) == 0.49f );
    assert ( limitter(-0.49f, 0.5f) == -0.49f );
    assert ( limitter(0.0051f, 0.005f) == 0.005f );
    assert ( limitter(-0.00501f, 0.005f) == -0.005f );

    cout << "speedLimitter is OK." << endl;
    
    
    //Test positionLoop()
    posi_t pos;
    pos.x = 1.1; pos.y = -0.01;
    positionLoop(&pos, 1.0f, 1.0f);
    assert (pos.x == 0.0f);
    assert (pos.y == 1.0f);
    pos.x = -0.1; pos.y = 1.4;
    positionLoop(&pos, 1.0f, 1.0f);
    assert (pos.x == 1.0f);
    assert (pos.y == 0.0f);
    pos.x = 0.0f; pos.y = 1.0f;
    positionLoop(&pos, 1.0f, 1.0f);
    assert (pos.x == 1.0f);
    assert (pos.y == 1.0f);
    //Check result check
    pos.x = 0.5f;
    pos.y = 0.5f;
    bool result = positionLoop(&pos , 1.0f, 1.0f);
    assert (result==false);
    pos.x = 1.0f;
    pos.y = 1.0f;
    result = positionLoop(&pos , 1.0f, 1.0f);
    assert (result==false);
    pos.x = 1.05f;
    pos.y = 1.05f;
    result = positionLoop(&pos , 1.0f, 1.0f);
    assert (result==true);
    pos.x = 1.05f;
    pos.y = 1.00f;
    result = positionLoop(&pos , 1.0f, 1.0f);
    assert (result==true);
    cout << "GismoLibrary::positionLoop() is OK" << endl;
    
    
    //Test attackCheck
    float fval2 = 0.0f;
    float size2 = 1.0f;
    attackCheck(fval2, &size2);
    bool size_test2 = true;
    if ( size2 != (1.0f-AG_DMG) ) size_test2 = false;
    assert(size_test2);
    assert(size2 == 1.0f-AG_DMG);
    size2 = 1.0f;
    fval2 = ATK_DIST+0.1;
    attackCheck(fval2, &size2);
    assert(size2 == 1.0f);
    cout << "GismoLibrary::attackCheck() is OK" << endl;

    size2 = 1.0f;
    fval2 = ATK_DIST;
    attackCheck(fval2, &size2);
    assert(size2 == 1.0f-AG_DMG);
    
    //Test deadCheck
    float dummy_size = 0.0001f;
    bool active = true;
    deadCheck( &dummy_size , &active );
    assert(active == false);
    assert(dummy_size == 0.0f);
    dummy_size = 1.0f;
    active = true;
    deadCheck( &dummy_size , &active );
    assert(active == true);
    cout << "GismoLibrary::deadCheck is OK" << endl;
    
    //Test Shape2Agent
    ag_shape_t shape;
    shape.nodes[0].x = 0.5f;
    shape.nodes[0].y = 0.5f;
    shape.nodes[1].x = 1.0f;
    shape.nodes[1].y = 1.0f;
    shape.node_count = 2;
    shape.edges[0].node_id_a = 0;
    shape.edges[0].node_id_b = 1;
    shape.edge_count = 1;
    ag_t tmpAg = shape2Agent(shape);
    assert(tmpAg.view == 0.005f);
    //assert(tmpAg.size == 0.011f);
    assert(tmpAg.mov == 0.35f);
    ag_shape_t shape2;
    shape2.node_count = 50000;
    ag_t tmpAg3 = shape2Agent(shape2);
    cout << tmpAg3.mov << endl;
    assert(tmpAg3.mov == MOV_MINIMUM);
    cout << "Shape2Agent.hpp::shape2Agent() is OK" << endl;
    
    //Test moveOnLine()
    posi_t posi = moveOnLine(0.5f, 0.0f, 0.0f, 1.0f, 1.0f);
    assert(posi.x == 0.5f && posi.y == 0.5f);
    posi = moveOnLine(1.0f, 0.0f, 0.0f, 1.0f, 1.0f);
    assert(posi.x == 1.0f && posi.y == 1.0f);
    posi = moveOnLine(0.5f, -1.0f, -1.0f, -2.0f, -2.0f);
    assert(posi.x == -1.5f && posi.y == -1.5f);
    posi = moveOnLine(0.0f, -1.0f, -1.0f, -2.0f, -2.0f);
    assert(posi.x == -1.0f && posi.y == -1.0f);
    posi = moveOnLine(0.5f, 0.0f, 0.0f, -1.0f, -2.0f);
    assert(posi.x == -0.5f && posi.y == -1.0f);

    //TestGetArraySize
    int iArray[137];
    posi_t posiArray[138];
    assert(getArraySize(iArray)==137);
    assert(getArraySize(posiArray)==138);
    cout << "TestGetArraySize.h::getArraySize() is ok." << endl;
    
    //Test lambda bang
    int myArg[2];
    myArg[0] = 12;
    myArg[1] = 13;
    gismo.bang("/lambdaTest", myArg);

    //TestSoundTrigger
    param_u params[4];
    params[0].ival = 0; //Genre
    params[1].ival = 1; //Song
    params[2].ival = 2; //Slice
    params[3].fval = 1.0f;//effect
    gismo.bang("/soundTrg" , &params);
    cout << "sound trigger is ok. If you could listen the RM sound" << endl;
    
    //Test shape2Sound
    ag_shape_t shapeForSound;
    shapeForSound.node_count = 12;
    shapeForSound.color = 0.50f;
    sound_t snd = shape2sound(shapeForSound,5);
    assert(snd.genre == 2);
    assert(snd.song == 5);
    shapeForSound.node_count = 6;
    shapeForSound.color = 1.0f;
    snd = shape2sound(shapeForSound,1137);
    assert(snd.genre == 0);
    assert(snd.song == 137);
    cout << "SoundTrigger::shape2Sound is OK" << endl;
    ag_t test;
    test.condition = CALM;
    ag2sound(&test, &snd);
    assert(snd.slice == 0);
    assert(snd.effect_val == EF_VAL_CALM);
    test.condition = RUN;
    ag2sound(&test, &snd);
    assert(snd.slice == 1);
    assert(snd.effect_val == EF_VAL_RUN);
    test.condition = CHASE;
    ag2sound(&test, &snd);
    assert(snd.slice == 2);
    assert(snd.effect_val == EF_VAL_CHASE);
    test.condition = DMG;
    ag2sound(&test, &snd);
    assert(snd.slice == 3);
    assert(snd.effect_val == EF_VAL_DMG);
    test.condition = DEATH;
    ag2sound(&test, &snd);
    assert(snd.slice == 4);
    assert(snd.effect_val == EF_VAL_DEATH);
    cout << "SoundTrigger::ag2Sound is OK" << endl;
    
}

void Test :: update(){

    
    
//    float fval = fade.update();
//    cout << "fval=" << fval << endl;
//    if(fval>0.5f) fade.reset();
//    fade.bang();
        
}


void Test::runVisualTest(visual_container_t* visual) {
    std::cout << " " << std::endl;
    std::cout << "Visual test methods are starting..." << std::endl;

    gismo.eventAdd("/ripple", ripple);
    
    //Test Bang Ripple
    cout << "Calling RippleManager::ripple.triger()....";
//    float args1[] = {0.25 ,0.5};
//    assert ( gismo.bang("/ripple", args1) == 1.0 );
//    float args2[] = {0.5 ,0.5};
//    assert ( gismo.bang("/ripple", args2) == 1.0 );
//    float args3[] = {0.75 ,0.5};
//    assert ( gismo.bang("/ripple", args3) == 1.0 );
    cout << "OK." << endl;
    
    //Test solo
    cout << "Calling Solo....";
    gismo.eventAdd("/solo", &visual->events.solo);
//    int soloID[] = {1 , isSolo};
//    assert(visEvents.bang("/solo", &soloID) == 1);
//    assert(visEvents.bang("/solo", &soloID) == 1);
    cout << "OK" << endl;
    
    
    //Test invert
//    cout << "Calling Invert...";
//    gismo.eventAdd("/invert", &visual->events.invert);
//    int invArg = 1;
//    assert(gismo.bang("/invert") == 1);
//    assert(gismo.bang("/invert") == 1);
//    cout << "OK" << endl;
    
    //Test line
//    cout << "Calling line through event....";
//    A2PLine line;
//    gismo.eventAdd("/line", &line);
//    float lineArgs[] = {0.25, 0.5, 0.75, 0.5};
//    assert ( gismo.bang("/line", lineArgs) == 1.0 );
//    cout << "OK" << endl;
    
    //Test nodebang
//    cout << "Calling node-bang through event....";
//    gismo.eventAdd("/lineNodeBang", &line.node);
//    float nodeDuration = 2000;
//    assert (gismo.bang("/lineNodeBang", &nodeDuration) == 1.0);
//    cout << "OK" << endl;
    
    //Test line
//    cout << "Calling visual.interaction through event....";
//    gismo.eventAdd("/line", &visual->motion.agent[1].interaction);
//    assert ( gismo.bang("/line", lineArgs) == 1.0 );
//    cout << "OK" << endl;
    
    //Test node bang through manager
//    cout << "Calling visual.node-bang through event....";
//    gismo.eventAdd("/nodeBang", &visual->motion.agent[1].interaction.node);
//    nodeDuration = 2000;
//    assert (gismo.bang("/nodeBang", &nodeDuration) == 1.0);
//    cout << "OK" << endl;
}

void Test::solo() {
    int id = ofRandom(1.0) * gismo.agents.count;
    
    param_u tmp[2];
    tmp[0].ival = id;
    tmp[1].fval = 1000;
    gismo.bang("/solo", &tmp);
    
    
    float args1[] = {gismo.getAgent(id)->posi.x ,gismo.getAgent(id)->posi.y};
    gismo.bang("/ripple", args1);
}


void Test::invert() {
    gismo.bang("/invert");
}

void Test::createShape(ag_shape_t* shape) {
    //Create random shape
    
    shape->node_count = 20;
    shape->edge_count = shape->node_count * (1.0 + frand());
    
    for(int i = 0; i < NODE_MAX; i++) {
        shape->nodes[i].x = (frand() - 0.5) * 0.1;
        shape->nodes[i].y = (frand() - 0.5) * 0.1;
    }
    
    for (int i = 0; i <  shape->edge_count; i++) {
        shape->edges[i].node_id_a = i % int(shape->node_count * 0.25);
        shape->edges[i].node_id_b = i % shape->node_count;
    }
    
}
