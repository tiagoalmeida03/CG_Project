//
//  ofApp.cpp
//  ProjetoCG_Tiago_Almeida_2021221615
//
//  Created by Tiago Almeida.
//

// Including necessary libraries
#include "ofApp.h"
#include <iostream>

//--------------------------------------------------------------
void ofApp::setup(){
    // Enabling depth testing for proper rendering of 3D objects
    glEnable(GL_DEPTH_TEST);
    ofDisableArbTex();

    // Setting up the background color and line width
    ofBackground(.05, .05, .05);
    glLineWidth(4);

    // Initializing various parameters for the scene
    view = 0; // View mode (default top view)
    ortogonal = false; // Projection mode flag (perspective or orthogonal)
    
    // Floor parameters
    floorX = 40;
    floorY = 20;
    floorZ = 0;
    floorW = gw();
    floorH = gh();

    // Building parameters
    buildingX = 10;
    buildingY = 5;
    buildingZ = 50;
    buildingW = 1.5 * floorW / floorX;
    buildingH = 1.5 * floorH / floorY;

    rotation = 0;
    elevator = 30;
    flagElevator == false;
    
    //Light Variables
    dirLight = true;
    pntLight = true;
    pntLight2 = true;
    dirVecTheta = 0;
    spotOn = false;
    autoMove = true;
    pointZtheta = 0;
    pointZtheta2 = 0;
    ambientOn = true;
    
    spotExponent = 0;
    spotCutoff = 1;
    spotTheta = 0;
    
    activateSkyBox = true;
    
    //Materials Variable
    mat = 0;
    customMat = true;
    customMatCoef = 1;
    
    //Images & Textures
    img1.load("sky.png");
    imgC.load("albedo.jpg");
    imgP.load("normalMap.jpg");
    imgR.load("water.jpg");
    
    px = 128;
    py = 128;
    img1.allocate(px, py, OF_IMAGE_COLOR);
    skyPixels = new unsigned char[px * py * 3];
    
    printData = false;
    
    // Generating random colors and building heights
    for (int i = 0; i < 50; i++){
        number = 1 + rand()%9;
        Colors.push_back(number);
    }

    for (int i = 0; i < 50; i++){
        number = 1 + rand()%9;
        Building_Height.push_back(number);
    }
}

//--------------------------------------------------------------
void ofApp::update(){
    // Update actions, e.g., rotation and elevator movement
    rotation++;

    if(flagElevator == true){
        elevator++;
        if(elevator == 425) flagElevator = false;
    } else if (flagElevator == false){
        elevator--;
        if(elevator == 25) flagElevator = true;
    }
    
    //Lights
    ofSetWindowTitle(ofToString(ofGetFrameRate()));
    
    if (pntLight) {
        //posi��o da luz pontual 1
        pointPos[0] = -floorW / (2*floorX);//x
        pointPos[1] = -floorH / (2*floorY);//y
        pointPos[2] = 50;//z
    }
    
    if (pntLight2) {
        //posi��o da luz pontual 2
        pointPos2[0] = gw() * .25;//x
        pointPos2[1] = gh() * .4;//y
        pointPos2[2] = 0;//z
    }
    
    if (dirLight) {
        //calculo da direcao da luz direcional
        float z = gh() * 0.25 * (cos(dirVecTheta * PI / 180.) * 0.5 + 0.45);
        float y = gh() * 0.5;
        float x = 0;
        dirVec3f = ofVec3f(x, y, z) - ofVec3f(0, 0, 0);
        dirVecTheta += 0.5;
    }
    
    //representa��o da posi��o da luz spot
    if (spotOn) {
        glColor3f(1, 1, 1);
        glPushMatrix();
        glTranslatef(spotPos[0], spotPos[1], spotPos[2]);
        glScalef(30, 30, 30);
        building_cube();
        glPopMatrix();
    }
    
    
    if (autoMove) {
        //calculo da posicao da luz pontual 1
        pointPos[0] = gw() * 0.5 * sin(3 * pointZtheta * PI / 180.0);
        pointPos[1] = gh() * 0.5 * cos(pointZtheta * PI / 180.0);
        pointPos[2] = 200 + 199 * cos(8 * pointZtheta * PI / 180.0);
        pointZtheta += 0.25;
        
        //calculo da posicao da luz pontual 2
        pointPos2[0] = gw() * 0.5 * sin(3 * pointZtheta2 * PI / 180.0);
        pointPos2[1] = gh() * 0.5 * cos(pointZtheta2 * PI / 180.0);
        pointPos2[2] = 200 + 199 * cos(8 * pointZtheta2 * PI / 180.0);
        pointZtheta2 += 0.25;

        //calculo da direcao da luz direcional
        float z = gh() * 0.25 * (cos(dirVecTheta * PI / 180.) * 0.5 + 0.45);
        float y = gh() * 0.5;
        float x = 0;
        dirVec3f = ofVec3f(x, y, z) - ofVec3f(0, 0, 0);
        dirVecTheta += 0.5;

        //calculo da direcao do spot
        spotDir[0] = cos(spotTheta * PI / 180.);
        spotDir[1] = sin(spotTheta * PI / 180.);
        spotTheta += 0.75;

    }
    else {
        //luz pontual
        //centro acima
        pointPos[0] = 0;
        pointPos[1] = 0;
        pointPos[2] = 90;

        //centro embaixo
        /*pointPos[0] = 0;
        pointPos[1] = 0;
        pointPos[2] = -90;*/
        //centro malha esquerda
        /*pointPos[0] = -gw()*0.25;
        pointPos[1] = 0;
        pointPos[2] = 90;*/
        //centro edge
        /*pointPos[0] = 0;
        pointPos[1] = -gh()*0.5;
        pointPos[2] = 100;*/


        //luz direcional
        //auto max
        dirVec3f = ofVec3f(0, gh()*0.5, gh()*0.25*0.95) - ofVec3f(0, 0, 0);
        //auto min
        //dirVec3f = ofVec3f(0, gh()*0.5, 0) - ofVec3f(0, 0, 0);
        //z+
        //dirVec3f = ofVec3f(0, 0, 1);
        //45 graus
        //dirVec3f = ofVec3f(0, 10, 10);
        

        //spot
        spotDir[0] = 0;
        spotDir[1] = 0;

     }
}

//--------------------------------------------------------------
void ofApp::draw(){
    glPushMatrix();
    // Drawing the scene

    // Applying perspective or orthogonal projection based on the flag
    if (ortogonal) {
        // Orthogonal projection
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        glOrtho(-gw() * .5, gw() *.5, gh() * .5, -gh() * .5, -1000, 10000);

        // Switching between different orthogonal views
        switch (view) {
            case 0: // top view
                lookat(0, 0, 1000, 0,0,0, 0,1,0);
                break;
            case 1: // front view
                lookat(0, gh() * 2, 150, 0, 0, 150, 0, 0, -1);
                break;
            case 2: // another front view
                lookat(0, gh() * 7.5, (gh() * 1.5) + 2500, 0, 0, 300, 0, 0, -1);
                break;
        }
    } else {
        // Perspective projection
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        perspective(60, 10, 1000);

        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();

        // Switching between different perspective views
        switch (view) {
            case 0: // top view
                glTranslatef(0, 0, -1500);
                break;
            case 1: // front view
                glTranslatef(0, 150, -1500);
                glRotatef(90, 1, 0, 0);
                break;
            case 2: // another front view
                lookat(0, 750, 1000, 0, 0, 0, 0, 0, -1);
                glTranslatef(0, -75, -100);
                break;
        }
    }
    
    //Define Lights
    glEnable(GL_LIGHTING);  //Activates Light
    glEnable(GL_NORMALIZE); //Normalize Normals
    glEnable(GL_COLOR_MATERIAL);
    glLightModeli(GL_LIGHT_MODEL_LOCAL_VIEWER, true);
    glLightModeli(GL_LIGHT_MODEL_COLOR_CONTROL, GL_SEPARATE_SPECULAR_COLOR);

    cityBuilder();
    materials();
    focusLight();
    pointLight();
    pointLight2();
    directionalLight();
    ambientLights();
    skyBox();
    
    printAllData();
    
    //Material's Name
    lookat(0, 0, gh()*0.9, 0, 0, 0, 0, 1, 0);
    glColor3f(1, 1, 1);
    if (customMat) {
        ofDrawBitmapString("custom", -gw() * 0.5 + 2, gh() * 0.5 - 15);
    }
    else {
        ofDrawBitmapString(Materiais[mat], -gw() * 0.5 + 2, gh() * 0.5 - 15);
    }
    
    //#################################################
    if (printData) {
        printAllData();
        printData = false;
    }

    // Restoring the previous transformation matrix
    ofPopMatrix();
}


//--------------------------------------------------------------
void ofApp::exit(){
    img1.clear();

}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    // Switch statement to handle different key presses
    switch (key) {
        case '1':
            // Disable back-face culling
            glDisable(GL_CULL_FACE);
            break;
        case '2':
            // Enable back-face culling and set cull face to GL_BACK
            glEnable(GL_CULL_FACE);
            glCullFace(GL_BACK);
            break;
        case '3':
            // Enable back-face culling and set cull face to GL_FRONT
            glEnable(GL_CULL_FACE);
            glCullFace(GL_FRONT);
            break;
        case '4':
            // Enable back-face culling and set cull face to GL_FRONT_AND_BACK
            glEnable(GL_CULL_FACE);
            glCullFace(GL_FRONT_AND_BACK);
            break;
        case 'g':
            // Set polygon mode to wireframe (GL_LINE)
            glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
            break;
        case 'f':
            // Set polygon mode to filled (GL_FILL)
            glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
            break;
        case 'v':
            // Cycle through different views (0, 1, 2) for perspective or orthogonal projection
            view++;
            if(view > 2){
                view = 0;
            }
            break;
        case 'o':
            // Toggle between orthogonal and perspective projections
            ortogonal = !ortogonal;
            break;
        case 'p':
            pntLight = !pntLight;
            break;
        case 'l':
            pntLight2 = !pntLight2;
            break;
        case 'd':
            dirLight = !dirLight;
            break;
        case 'c':
            customMat = !customMat;
            break;
        case OF_KEY_RIGHT:
            customMatCoef++;
            mat++;
            if (mat > 19){
                mat = 18;
            }
            if (customMatCoef > 128) {
                customMatCoef = 128;
            }
            break;
        case OF_KEY_LEFT:
            customMatCoef--;
            mat--;
            if (mat < 0){
                mat = 0;
            }
            if (customMatCoef < 0) {
                customMatCoef = 0;
            }
            break;
        case '+':
            spotCutoff++;
            if (spotCutoff > 180) {
                spotCutoff = 180;
            }
            break;
        case '-':
            spotCutoff--;
            if (spotCutoff < 1) {
                spotCutoff = 1;
            }
            break;
        case 'm':
            glShadeModel(GL_FLAT);
            break;
        case 'n':
            glShadeModel(GL_SMOOTH);
            break;
        case 's':
            spotOn = !spotOn;
            break;
        case OF_KEY_UP:
            spotExponent++;
            if (spotExponent > 128) {
                spotExponent = 128;
            }
            break;
        case OF_KEY_DOWN:
            spotExponent--;
            if (spotExponent < 0) {
                spotExponent = 0;
            }
            break;
        case 'q':
            autoMove = !autoMove;
            break;
        case 'a':
            ambientOn = !ambientOn;
            break;
        case '0':
            activateSkyBox = !activateSkyBox;
            break;
    }
    
    printData = true;
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){
    
}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseScrolled(int x, int y, float scrollX, float scrollY){

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){
    setup();
}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){

}

//--------------------------------------------------------------
void ofApp::focusLight(){
    //luz foco left

    //posicao
    spotPos[0] = -gw() * 0.25;
    spotPos[1] = 0.;
    spotPos[2] = 150.;
    spotPos[3] = 1.;


    //direcao
    //spotDir[0] = 0.;
    //spotDir[1] = 0.;
    spotDir[2] = -1.;
    //spotDir[3] = 0.;N�o tem a 4 coordenada, � sempre vetor

    //ambiente
    spotAmb[0] = 0.;//R
    spotAmb[1] = 0.;//G
    spotAmb[2] = 0.;//B
    spotAmb[3] = 0.;//constante

    //difusa
    spotDif[0] = 1.;//R
    spotDif[1] = 1.;//G
    spotDif[2] = 1.;//B
    spotDif[3] = 1.;//constante

    //specular
    spotSpecular[0] = 1.;//R
    spotSpecular[1] = 1.;//G
    spotSpecular[2] = 1.;//B
    spotSpecular[3] = 1.;//constante

    //concentracao
    spotExponent = 1;//0 - 128

    //angulo
    spotCutoff = 1;//0 - 180

    glLightfv(GL_LIGHT2, GL_POSITION, spotPos);
    glLightfv(GL_LIGHT2, GL_SPOT_DIRECTION, spotDir);

    glLightfv(GL_LIGHT2, GL_AMBIENT, spotAmb);
    glLightfv(GL_LIGHT2, GL_DIFFUSE, spotDif);
    glLightfv(GL_LIGHT2, GL_SPECULAR, spotSpecular);

    glLightf(GL_LIGHT2, GL_SPOT_EXPONENT, spotExponent);
    glLightf(GL_LIGHT2, GL_SPOT_CUTOFF, spotCutoff);

    //atenua��o
    spotAtC = 1.;
    spotAtL = 0.;
    spotAtQ = 0.;
    glLightf(GL_LIGHT2, GL_CONSTANT_ATTENUATION, spotAtC);
    glLightf(GL_LIGHT2, GL_LINEAR_ATTENUATION, spotAtL);
    glLightf(GL_LIGHT2, GL_QUADRATIC_ATTENUATION, spotAtQ);
    if (spotOn) {
        glEnable(GL_LIGHT2);
    }
    else {
        glDisable(GL_LIGHT2);
    }
}

//--------------------------------------------------------------
void ofApp::pointLight(){
    //componentes da luz pontual
    pointPos[3] = 1;

    pointAmb[0] = 0.;//R
    pointAmb[1] = 0.;//G
    pointAmb[2] = 0.;//B
    pointAmb[3] = 1.;//constante

    pointDif[0] = 0.8;//R
    pointDif[1] = 0.2;//G
    pointDif[2] = 0.8;//B
    pointDif[3] = 1.;//constante

    pointSpec[0] = 0.5;//R
    pointSpec[1] = 0.2;//G
    pointSpec[2] = 0.5;//B
    pointSpec[3] = 1.;//constante

    glLightfv(GL_LIGHT1, GL_POSITION, pointPos);
    glLightfv(GL_LIGHT1, GL_AMBIENT, pointAmb);
    glLightfv(GL_LIGHT1, GL_DIFFUSE, pointDif);
    glLightfv(GL_LIGHT1, GL_SPECULAR, pointSpec);

    glLightf(GL_LIGHT1, GL_CONSTANT_ATTENUATION, 1);
    glLightf(GL_LIGHT1, GL_LINEAR_ATTENUATION, 0.0001);
    glLightf(GL_LIGHT1, GL_QUADRATIC_ATTENUATION, 0.00002);
    if (pntLight) {
        glEnable(GL_LIGHT1);
    }
    else {
        glDisable(GL_LIGHT1);
    }
}

//--------------------------------------------------------------
void ofApp::pointLight2(){
    //componentes da luz pontual
    pointPos2[3] = 1;

    pointAmb2[0] = 0.;//R
    pointAmb2[1] = 0.;//G
    pointAmb2[2] = 0.;//B
    pointAmb2[3] = 1.;//constante

    pointDif2[0] = 0.8;//R
    pointDif2[1] = 0.2;//G
    pointDif2[2] = 0.8;//B
    pointDif2[3] = 1.;//constante

    pointSpec2[0] = 0.5;//R
    pointSpec2[1] = 0.2;//G
    pointSpec2[2] = 0.5;//B
    pointSpec2[3] = 1.;//constante

    glLightfv(GL_LIGHT3, GL_POSITION, pointPos2);
    glLightfv(GL_LIGHT3, GL_AMBIENT, pointAmb2);
    glLightfv(GL_LIGHT3, GL_DIFFUSE, pointDif2);
    glLightfv(GL_LIGHT3, GL_SPECULAR, pointSpec2);

    glLightf(GL_LIGHT3, GL_CONSTANT_ATTENUATION, 1);
    glLightf(GL_LIGHT3, GL_LINEAR_ATTENUATION, 0.0001);
    glLightf(GL_LIGHT3, GL_QUADRATIC_ATTENUATION, 0.00002);
    if (pntLight2) {
        glEnable(GL_LIGHT3);
    }
    else {
        glDisable(GL_LIGHT3);
    }
}

//--------------------------------------------------------------
void ofApp::directionalLight(){
    //luz direcional
    dirVec[0] = dirVec3f.x;//x
    dirVec[1] = dirVec3f.y;//y
    dirVec[2] = dirVec3f.z;//z
    dirVec[3] = 0;//vetor - dire��o!

    dirAmb[0] = 0;//R
    dirAmb[1] = 0.0;//G
    dirAmb[2] = 0.0;//B
    dirAmb[3] = 1.;//constante

    dirDif[0] = 1;//R
    dirDif[1] = 1;//G
    dirDif[2] = 0;//B
    dirDif[3] = 1.;//constante

    dirSpec[0] = 0.5;//R
    dirSpec[1] = 0.5;//G
    dirSpec[2] = 0.5;//B
    dirSpec[3] = 1.;//constante

    glLightfv(GL_LIGHT0, GL_POSITION, dirVec);
    glLightfv(GL_LIGHT0, GL_AMBIENT, dirAmb);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, dirDif);
    glLightfv(GL_LIGHT0, GL_SPECULAR, dirSpec);

    if (dirLight) {
        glEnable(GL_LIGHT0);
    }
    else {
        glDisable(GL_LIGHT0);
    }
}

void ofApp::ambientLights(){
    //#################################################
    //fonte de luz que s� tem componente ambiente
    //n�o conta como uma fonte de luz LIGHT0 - LIGHT8
    if (ambientOn) {
        ambientLight[0] = .3;//R
        ambientLight[1] = .3;//G
        ambientLight[2] = .3;//B
        ambientLight[3] = 1;//useless
    }
    else {
        ambientLight[0] = 0.;
        ambientLight[1] = 0.;
        ambientLight[2] = 0.;
        ambientLight[3] = 1;
    }
    glLightModelfv(GL_LIGHT_MODEL_AMBIENT, ambientLight);
    //#################################################
}

//--------------------------------------------------------------
void ofApp::materials(){
    //Define Material
    if (!customMat) {
        //material pr� definido
        loadMaterial(mat);
    }
    else {
        //material customizado
        customMatAmb[0] = 0.1;//R
        customMatAmb[1] = 0.1;//G
        customMatAmb[2] = 0.1;//B
        customMatAmb[3] = 1.;

        customMatDif[0] = 0.5;//R
        customMatDif[1] = 0.5;//G
        customMatDif[2] = 0.5;//B
        customMatDif[3] = 1.;

        customMatSpec[0] = 1.;//R
        customMatSpec[1] = 1.;//G
        customMatSpec[2] = 1.;//B
        customMatSpec[3] = 1.;
            
        glMaterialfv(GL_FRONT, GL_AMBIENT, customMatAmb);
        glMaterialfv(GL_FRONT, GL_DIFFUSE, customMatDif);
        glMaterialfv(GL_FRONT, GL_SPECULAR, customMatSpec);
        glMaterialf(GL_FRONT, GL_SHININESS, customMatCoef);
    }
}

//--------------------------------------------------------------
void ofApp::cityBuilder(){
    glPushMatrix();
    
    // Drawing the floor using the grid_unit function
    glPushMatrix();
    glColor3f(.5, .5, .5);
    glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT);
    glColorMaterial(GL_FRONT_AND_BACK, GL_DIFFUSE);
    glColorMaterial(GL_FRONT_AND_BACK, GL_SPECULAR);
    glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);
    glScalef(floorW, floorH, floorZ);
    grid_unit(floorX, floorY, imgC);
    glPopMatrix();
   
    // Drawing city buildings
    glPushMatrix();
    city(Colors, Building_Height, flagElevator, elevator, imgP);
    glPopMatrix();

    // Drawing a cylinder in the middle
    /*glEnable(GL_TEXTURE1);
    imgC.bind();
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);*/
    glPushMatrix();
    glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT);
    glColorMaterial(GL_FRONT_AND_BACK, GL_DIFFUSE);
    glColorMaterial(GL_FRONT_AND_BACK, GL_SPECULAR);
    glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);
    glTranslatef(-floorW / (2*floorX), -floorH / (2*floorY), 0);
    glScaled(floorW*3 / floorX, floorH*3 / floorY, 100);
    drawCylinder();
    /*imgC.unbind();
    glDisable(GL_TEXTURE1);*/
    glPopMatrix();

    // Drawing a pyramid with custom vertices above the cylinder
    /*glEnable(GL_TEXTURE2);
    imgC.bind();
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);*/
    glPushMatrix();
    glColor3f(0, .5, .5);
    glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT);
    glColorMaterial(GL_FRONT_AND_BACK, GL_DIFFUSE);
    glColorMaterial(GL_FRONT_AND_BACK, GL_SPECULAR);
    glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);
    glTranslatef(-floorW / (2*floorX), -floorH / (2*floorY), 100);
    glScaled(floorW*3 / floorX, floorH*3 / floorY, 500);
    glRotatef(rotation, 0, 0, 1);
    loadMaterial(1);
    pyramid();
    /*imgC.unbind();
    glDisable(GL_TEXTURE2);*/
    glPopMatrix();

    // Drawing a cube above the pyramid
    glPushMatrix();
    glColor3f(.5, 0, .5);
    glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT);
    glColorMaterial(GL_FRONT_AND_BACK, GL_DIFFUSE);
    glColorMaterial(GL_FRONT_AND_BACK, GL_SPECULAR);
    glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);
    glTranslatef(-floorW / (2*floorX), -floorH / (2*floorY), 400);
    glScaled(floorW*3 / floorX, floorH*3 / floorY, 100);
    glRotatef(rotation, 0, 0, 1);
    glRotatef(45, 1, 1, 1);
    loadMaterial(16);
    building_mesh(50, 50, imgR);
    glPopMatrix();
    
    glPopMatrix();
}

//--------------------------------------------------------------

void ofApp::skyBox() {
    if(activateSkyBox){
        //implementação da skybox
        glEnable(GL_TEXTURE0);
        glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
        img1.bind();
        glPushMatrix();
        glRotatef(rx, 1, 0, 0);
        glRotatef(ry, 0, 1, 0);
        glRotatef(rz, 0, 0, 1);
        glScalef(gw() * 50, gw() * 50., gw() * 50.);
        sphereSkyBox(64);
        glPopMatrix();
        
        img1.unbind();
        glDisable(GL_TEXTURE0);
        
        rx += 0.1;
        ry += 0.2;
        rz += 0.15;
    }
}

//--------------------------------------------------------------
void ofApp::printAllData() {
    cout << endl << "#######################################";
    //projectionMatrix
    coutProjectionMatrix();
    cout << endl << "--------------------------------";
    //modelViewMatrix
    cout << endl << "modelview matrix" << endl;
    printMatrix(mview);
    cout << endl << "--------------------------------";
    //ambient source
    cout << endl << "ambient source RGB = " << ambientLight[0] << " " << ambientLight[1] << " " << ambientLight[2];
    cout << endl << "--------------------------------";
    //luz direcional
    cout << endl << "lur direcional";
    cout << endl << "dirOn = " << dirLight;
    cout << endl << "direction = " << "[" << dirVec[0] << ", " << dirVec[1] << ", " << dirVec[2] << "]";
    cout << endl << "Luz_dir Ambiente RGB = " << dirAmb[0] << " " << dirAmb[1] << " " << dirAmb[2];
    cout << endl << "Luz_dir Difusa RGB = " << dirDif[0] << " " << dirDif[1] << " " << dirDif[2];
    cout << endl << "Luz_dir Especular RGB = " << dirSpec[0] << " " << dirSpec[1] << " " << dirSpec[2];
    cout << endl << "--------------------------------";
    //luz pontual
    cout << endl << "lur pontual 1";
    cout << endl << "pointOn = " << pntLight;
    cout << endl << "point light = " << "[" << pointPos[0] << ", " << pointPos[1] << ", " << pointPos[2] << "]";
    cout << endl << "Luz_point Ambiente RGB = " << pointAmb[0] << " " << pointAmb[1] << " " << pointAmb[2];
    cout << endl << "Luz_point Difusa RGB = " << pointDif[0] << " " << pointDif[1] << " " << pointDif[2];
    cout << endl << "Luz_point Especular RGB = " << pointSpec[0] << " " << pointSpec[1] << " " << pointSpec[2];
    cout << endl << "Luz_point attenuation CLQ= " << pointAtC << " " << pointAtL << " " << pointAtQ;
    cout << endl << "--------------------------------";
    //luz pontual2
    cout << endl << "lur pontual 2";
    cout << endl << "pointOn = " << pntLight2;
    cout << endl << "point light = " << "[" << pointPos2[0] << ", " << pointPos2[1] << ", " << pointPos2[2] << "]";
    cout << endl << "Luz_point Ambiente RGB = " << pointAmb2[0] << " " << pointAmb2[1] << " " << pointAmb2[2];
    cout << endl << "Luz_point Difusa RGB = " << pointDif2[0] << " " << pointDif2[1] << " " << pointDif2[2];
    cout << endl << "Luz_point Especular RGB = " << pointSpec2[0] << " " << pointSpec2[1] << " " << pointSpec2[2];
    cout << endl << "Luz_point attenuation CLQ= " << pointAtC2 << " " << pointAtL2 << " " << pointAtQ2;
    cout << endl << "--------------------------------";
    //luz foco
    cout << endl << "luz spotlight";
    cout << endl << "spotOn = " << spotOn;
    cout << endl << "spot light pos = " << "[" << spotPos[0] << ", " << spotPos[1] << ", " << spotPos[2] << "]";
    cout << endl << "spot light dir = " << "[" << spotDir[0] << ", " << spotDir[1] << ", " << spotDir[2] << "]";
    cout << endl << "Luz_spot Ambiente RGB = " << spotAmb[0] << " " << spotAmb[1] << " " << spotAmb[2];
    cout << endl << "Luz_spot Difusa RGB = " << spotDif[0] << " " << spotDif[1] << " " << spotDif[2];
    cout << endl << "Luz_spot Especular RGB = " << spotSpecular[0] << " " << spotSpecular[1] << " " << spotSpecular[2];
    cout << endl << "spotExponent = " << spotExponent;
    cout << endl << "spotCutoff = " << spotCutoff;
    cout << endl << "Luz_spot attenuation CLQ= " << spotAtC << " " << spotAtL << " " << spotAtQ;
    cout << endl << "--------------------------------";
    //material
    cout << endl << "Material properties";
    cout << endl << "customMat = " << customMat;
    cout << endl << "customMat Ambiente RGB = " << customMatAmb[0] << " " << customMatAmb[1] << " " << customMatAmb[2];
    cout << endl << "customMat Difusa RGB = " << customMatDif[0] << " " << customMatDif[1] << " " << customMatDif[2];
    cout << endl << "customMat Especular RGB = " << customMatSpec[0] << " " << customMatSpec[1] << " " << customMatSpec[2];
    cout << endl << "customMatCoef = " << customMatCoef;
    cout << endl << "--------------------------------";
    //localviewer
    cout << endl << "localViewer = " << localViewer;
    cout << endl << "#######################################";
}

/* ofApp.cpp */
