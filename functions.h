//
//  functions.h
//  ProjetoCG_Tiago_Almeida_2021221615
//
//  Created by Tiago Almeida.
//
// functions.h


// Header guard to prevent multiple inclusion
#ifndef functions_h
#define functions_h

// Function to get the window width
inline float gw() {
    return ofGetWidth();
}

// Function to get the window height
inline float gh() {
    return ofGetHeight();
}

// Function to calculate the cross product of two vectors
inline ofVec3f cross(ofVec3f A, ofVec3f B) {
    ofVec3f aux;
    aux.x = A.y * B.z - A.z * B.y;
    aux.y = A.z * B.x - A.x * B.z;
    aux.z = A.x * B.y - A.y * B.x;

    return aux;
}

// LookAt Camera function
inline void lookat(
    GLfloat camX,
    GLfloat camY,
    GLfloat camZ,
    GLfloat targetX,
    GLfloat targetY,
    GLfloat targetZ,
    GLfloat upX,
    GLfloat upY,
    GLfloat upZ)
{
    // Define vectors for camera, target, and up
    ofVec3f cam = ofVec3f(camX, camY, camZ);
    ofVec3f target = ofVec3f(targetX, targetY, targetZ);
    ofVec3f up = ofVec3f(upX, upY, upZ);

    // Calculate camera coordinate system axes
    ofVec3f N = cam - target;
    N = N.normalized();
    ofVec3f U = cross(up, N);
    U = U.normalized();
    ofVec3f V = cross(N, U);
    V = V.normalized();

    // Create a transformation matrix for the camera
    GLfloat camTransformMatrix[4][4] = {
        {U.x, V.x, N.x, 0},
        {U.y, V.y, N.y, 0},
        {U.z, V.z, N.z, 0},
        {-U.dot(cam), -V.dot(cam), -N.dot(cam), 1}
    };

    // Set the modelview matrix using the calculated transformation matrix
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glMultMatrixf(&camTransformMatrix[0][0]);
}

/********************************************************************************************************************************************************************/
// Function to calculate the frustum of the perspective projection
// These calculations use triangle similarity, as explained in slide 51 of Theory 6
inline void perspective(GLfloat theta, GLfloat alpha, GLfloat beta) {
    // Set the projection matrix to a perspective projection
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    // Calculate parameters for the perspective projection
    GLfloat tan = tanf(theta * 0.5 * PI / 180.0);
    GLfloat d = (gh() / 2.0) / tan;
    GLfloat nearClip = d / alpha;
    GLfloat farClip = d * beta;
    GLfloat ymax = nearClip * tan;
    GLfloat xmax = (gw() / gh()) * ymax;

    // Adjust ymax for proper orientation
    ymax = -ymax;

    // Set the frustum using the calculated parameters
    glFrustum(-xmax, xmax, -ymax, ymax, nearClip, farClip);
}

//print projectio matrix
inline void coutProjectionMatrix() {

    GLfloat Matriz[4][4];
    cout << endl << "Projection Matrix" << endl;
    glGetFloatv(GL_PROJECTION_MATRIX, &Matriz[0][0]);

    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            cout << Matriz[j][i] << " ";
        }
        cout << endl;
    }
    //return;
}

//print de matrix 4x4
inline void printMatrix(GLfloat m[][4]) {
    cout << endl << "Matrix 4x4" << endl;
    cout << "[";
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            cout << m[j][i] << " ";
        }
        cout << ";";
    }
    cout << "]";
    cout << endl << "matrix" << endl;
}

inline GLfloat getMultiNoise(float x, float y, float f[], float a[], int numBands) {
    float noise = 0;
    float maxAmp = 0.;

    for (int i = 0; i < numBands; i++) {
        noise += a[i] * ofNoise(f[i] * x, f[i] * y);
        maxAmp += a[i];
    }
    return noise / maxAmp;
}



#endif /* functions_h */
