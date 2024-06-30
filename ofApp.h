//
//  ofApp.h
//  ProjetoCG_Tiago_Almeida_2021221615
//
//  Created by Tiago Almeida.
//

// Header guards to prevent multiple inclusion
#pragma once

// Including necessary openFrameworks and custom headers
#include "ofMain.h"
#include "draw_functions.h"
#include "functions.h"
#include "city.h"
#include "materiais.h"
#include <cmath> //Ver se efetivamente é necessário adicionar esta biblioteca

// Declaration of the main application class
class ofApp : public ofBaseApp{

public:
    // OF required functions
    void setup() override;
    void update() override;
    void draw() override;
    void exit() override;
    void focusLight();
    void pointLight();
    void pointLight2();
    void directionalLight();
    void ambientLights();
    void materials();
    void cityBuilder();

    void skyBox();
    
    // Input handling functions
    void keyPressed(int key) override;
    void keyReleased(int key) override;
    void mouseMoved(int x, int y) override;
    void mouseDragged(int x, int y, int button) override;
    void mousePressed(int x, int y, int button) override;
    void mouseReleased(int x, int y, int button) override;
    void mouseScrolled(int x, int y, float scrollX, float scrollY) override;
    void mouseEntered(int x, int y) override;
    void mouseExited(int x, int y) override;
    void windowResized(int w, int h) override;
    void dragEvent(ofDragInfo dragInfo) override;
    void gotMessage(ofMessage msg) override;

    // Floor Variables
    GLfloat floorW, floorH, floorZ;
    GLint floorX, floorY;
    
    // Building Variables
    GLfloat buildingW, buildingH, buildingZ;
    GLint buildingX, buildingY;
    
    // Variables for actions
    GLfloat rotation;
    GLfloat elevator;
    bool flagElevator;
    
    // Camera Variables
    int view;
    bool ortogonal;
    
    //Light Variables
    bool dirLight;
    bool pntLight;
    bool pntLight2;
    bool localViewer;
    bool autoMove;
    bool ambientOn;
    
    //skybox
    float rx, ry, rz;
    
    ofImage img1;
    ofImage imgP;
    ofImage imgC;
    ofImage imgR;
    
    GLfloat ambientLight[4];

    GLfloat dirVec[4];
    GLfloat dirAmb[4];
    GLfloat dirDif[4];
    GLfloat dirSpec[4];
    ofVec3f dirVec3f;
    GLfloat dirVecTheta;

    GLfloat pointPos[4];
    GLfloat pointPos2[4];
    GLfloat pointAmb[4];
    GLfloat pointAmb2[4];
    GLfloat pointDif[4];
    GLfloat pointDif2[4];
    GLfloat pointSpec[4];
    GLfloat pointSpec2[4];
    GLfloat pointZtheta;
    GLfloat pointZtheta2;
    GLfloat pointAtC, pointAtL, pointAtQ;
    GLfloat pointAtC2, pointAtL2, pointAtQ2;

    GLfloat spotPos[4];
    GLfloat spotDir[3];
    GLfloat spotAmb[4];
    GLfloat spotDif[4];
    GLfloat spotSpecular[4];
    GLfloat spotExponent;
    GLfloat spotCutoff;
    GLfloat spotTheta;
    GLfloat spotAtC, spotAtL, spotAtQ;
    bool spotOn;
    
    //Material Variables
    int mat;
    bool customMat;
    GLint customMatCoef;
    
    //Sphere Variable
    bool activateSkyBox;
    unsigned char* skyPixels = NULL;
    int px, py, numPixels;
    
    //texturas
    ofImage bump;
    unsigned char* pixels;
    unsigned char* normalPixels = NULL;
    ofImage albedo;
    ofImage normalMap;
    ofPixels p;
    ofImage world;
    bool originalOrBump;
    float bumpScale;
    
    //water
    float phaseX;
    float phaseY;
    float freqs[10];
    float amps[10];
    ofImage waterTex;
    vector<ofVec3f> vertexes;
    vector<ofVec3f> normals;
    vector<ofVec2f> texCoords;
    
    GLfloat mview[4][4];

    //print data
    bool printData;
    void printAllData();
    GLfloat customMatAmb[4];
    GLfloat customMatDif[4];
    GLfloat customMatSpec[4];
    
    // Vectors and Variables for randomizing colors and building heights
    std::vector<int> Colors;
    std::vector<int> Building_Height;
    int number;
    
};  /* ofApp.h */
