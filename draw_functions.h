//
//  draw_functions.h
//  ProjetoCG_Tiago_Almeida_2021221615
//
//  Created by Tiago Almeida.
//
// draw_functions.h

// Including necessary openFrameworks and custom headers
#include "ofMain.h"
#include "ofApp.h"

// Header guard to prevent multiple inclusion
#ifndef draw_functions_h
#define draw_functions_h

// Function for drawing a cube representing a building
inline void building_cube() {
    glPushMatrix();
    GLfloat p = 0.5;
    glBegin(GL_QUADS);

    // Front face
    glNormal3f(0, 0, 1);
    glVertex3f(-p, -p, p);
    glVertex3f(-p, p, p);
    glVertex3f(p, p, p);
    glVertex3f(p, -p, p);

    // Back face
    glNormal3f(0, 0, -1);
    glVertex3f(-p, -p, -p);
    glVertex3f(p, -p, -p);
    glVertex3f(p, p, -p);
    glVertex3f(-p, p, -p);

    // Top face
    glNormal3f(0, -1, 0);
    glVertex3f(-p, -p, -p);
    glVertex3f(-p, -p, p);
    glVertex3f(p, -p, p);
    glVertex3f(p, -p, -p);

    // Bottom face
    glNormal3f(0, 1, 0);
    glVertex3f(-p, p, p);
    glVertex3f(-p, p, -p);
    glVertex3f(p, p, -p);
    glVertex3f(p, p, p);

    // Left face
    glNormal3f(-1, 0, 0);
    glVertex3f(-p, -p, p);
    glVertex3f(-p, -p, -p);
    glVertex3f(-p, p, -p);
    glVertex3f(-p, p, p);

    // Right face
    glNormal3f(1, 0, 0);
    glVertex3f(p, -p, p);
    glVertex3f(p, p, p);
    glVertex3f(p, p, -p);
    glVertex3f(p, -p, -p);

    glEnd();
    glPopMatrix();
}

// Function for drawing a floor using mesh
inline void grid_unit(GLint m, GLint n, ofImage texture) {
    GLfloat x_start = -0.5;
    GLfloat y_start = -0.5;
    GLfloat x_step = 1.0 / GLfloat(m);
    GLfloat y_step = 1.0 / GLfloat(n);
    
    glEnable(GL_TEXTURE_2D);
    texture.bind();

    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
    //glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    
    glBegin(GL_QUADS);
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            glNormal3f(0, 0, 1);
            glTexCoord2f(0,0);
            glVertex2d(i * x_step + x_start, j * y_step + y_start);
            glTexCoord2f(0,1);
            glVertex2d(i * x_step + x_start, (j + 1) * y_step + y_start);
            glTexCoord2f(1,1);
            glVertex2d((i + 1) * x_step + x_start, (j + 1) * y_step + y_start);
            glTexCoord2f(1,0);
            glVertex2d((i + 1) * x_step + x_start, j * y_step + y_start);
        }
    }
    glEnd();
    texture.unbind();
    glDisable(GL_TEXTURE_2D);
}

// Function for drawing a building using mesh
inline void building_mesh(GLint numSegments, GLint numGridCells, ofImage texture) {
    glPushMatrix();
    
    // Back face
    glPushMatrix();
    glTranslated(0., 0., -0.5);
    glRotated(180, 0, 1, 0);
    grid_unit(numGridCells, numGridCells, texture);
    glPopMatrix();

    // Top face
    glPushMatrix();
    glTranslated(0., -0.5, 0.);
    glRotated(90, 1, 0, 0);
    grid_unit(numGridCells, numGridCells, texture);
    glPopMatrix();

    // Bottom face
    glPushMatrix();
    glTranslated(0., 0.5, 0.);
    glRotated(-90, 1, 0, 0);
    grid_unit(numGridCells, numGridCells, texture);
    glPopMatrix();

    // Left face
    glPushMatrix();
    glTranslated(-0.5, 0., 0.);
    glRotated(-90, 0, 1, 0);
    grid_unit(numGridCells, numGridCells, texture);
    glPopMatrix();

    // Right face
    glPushMatrix();
    glTranslated(0.5, 0., 0.);
    glRotated(90, 0, 1, 0);
    grid_unit(numGridCells, numGridCells, texture);
    glPopMatrix();

    // Front face
    glPushMatrix();
    glTranslated(0., 0., 0.5);
    grid_unit(numGridCells, numGridCells, texture);
    glPopMatrix();

    glPopMatrix();
}

// Function for drawing a cylinder
inline void drawCylinder() {
    glPushMatrix();

    GLfloat radius = 0.5;
    GLfloat height = 1.0;
    GLint slices = 20;

    // Set color or material properties if needed
    glColor3f(1, 1, 1);

    // Draw the top circle
    glBegin(GL_TRIANGLE_FAN);
    glVertex3f(0, 0, 0); // Center of the top circle
    for (int i = 0; i <= slices; ++i) {
        GLfloat theta = (2.0 * M_PI * i) / slices;
        GLfloat x = radius * cos(theta);
        GLfloat y = radius * sin(theta);
        glVertex3f(x, y, 0);
    }
    glEnd();

    // Draw the sides (mesh)
    glBegin(GL_QUAD_STRIP);
    for (int i = 0; i <= slices; ++i) {
        GLfloat theta = (2.0 * M_PI * i) / slices;
        GLfloat x = radius * cos(theta);
        GLfloat y = radius * sin(theta);

        glNormal3f(x, y, 0);          // Normal dos lados
        glVertex3f(x, y, 0);          // Bottom point
        glVertex3f(x, y, height);     // Top point
    }
    glEnd();

    // Draw the bottom circle
    glBegin(GL_TRIANGLE_FAN);
    glVertex3f(0, 0, height); // Center of the bottom circle
    for (int i = slices; i >= 0; --i) {
        GLfloat theta = (2.0 * M_PI * i) / slices;
        GLfloat x = radius * cos(theta);
        GLfloat y = radius * sin(theta);
        glVertex3f(x, y, height);
    }
    glEnd();

    glPopMatrix();
}

inline void pyramid(){
    glPushMatrix();
    
    GLfloat p = 0.5;
    
    // Front face
    glPushMatrix();
    glNormal3f(0, 0, 1);
    glBegin(GL_TRIANGLES);
    glVertex3f(0, 0, p);
    glVertex3f(p, p, 0);
    glVertex3f(p, -p, 0);
    glEnd();
    glPopMatrix();
    
    // Back face
    glPushMatrix();
    glNormal3f(0, 0, -1);
    glBegin(GL_TRIANGLES);
    glVertex3f(0, 0, p);
    glVertex3f(-p, p, 0);
    glVertex3f(-p, -p, 0);
    glEnd();
    glPopMatrix();
    
    // Left face
    glPushMatrix();
    glNormal3f(-1, 0, 0);
    glBegin(GL_TRIANGLES);
    glVertex3f(0, 0, p);
    glVertex3f(p, p, 0);
    glVertex3f(-p, p, 0);
    glEnd();
    glPopMatrix();
    
    // Right face
    glPushMatrix();
    glNormal3f(1, 0, 0);
    glBegin(GL_TRIANGLES);
    glVertex3f(0, 0, p);
    glVertex3f(-p, -p, 0);
    glVertex3f(p, -p, 0);
    glEnd();
    glPopMatrix();
    
    // Bottom face
    glPushMatrix();
    glNormal3f(0, 0, -1);
    glBegin(GL_QUADS);
    glVertex3f(p, p, 0);
    glVertex3f(-p, p, 0);
    glVertex3f(-p, -p, 0);
    glVertex3f(p, -p, 0);
    glEnd();
    glPopMatrix();
    
    glPopMatrix();
}


inline void sphereSkyBox(int res) {
    float dtheta = PI / float(res);
    float dphi = 2 * PI / float(res);

    for (int i = 0; i < res; i++) {
        for (int j = 0; j < res; j++) {
            glBegin(GL_QUADS);

            float x1 = sin(i * dtheta) * cos(j * dphi);
            float y1 = sin(i * dtheta) * sin(j * dphi);
            float z1 = cos(i * dtheta);
            float tx1 = i / float(res);
            float ty1 = j / float(res);
            ofVec3f n1 = ofVec3f(-x1, -y1, -z1);
            glTexCoord2f(ty1, tx1);
            glNormal3f(n1.x, n1.y, n1.z);
            glVertex3f(x1, y1, z1);

            float x2 = sin(i * dtheta) * cos((j + 1) * dphi);
            float y2 = sin(i * dtheta) * sin((j + 1) * dphi);
            float z2 = cos(i * dtheta);
            float tx2 = i / float(res);
            float ty2 = (j + 1) / float(res);
            ofVec3f n2 = ofVec3f(-x2, -y2, -z2);
            glTexCoord2f(ty2, tx2);
            glNormal3f(n2.x, n2.y, n2.z);
            glVertex3f(x2, y2, z2);

            float x3 = sin((i + 1) * dtheta) * cos((j + 1) * dphi);
            float y3 = sin((i + 1) * dtheta) * sin((j + 1) * dphi);
            float z3 = cos((i + 1) * dtheta);
            float tx3 = (i + 1) / float(res);
            float ty3 = (j + 1) / float(res);
            ofVec3f n3 = ofVec3f(-x3, -y3, -z3);
            glTexCoord2f(ty3, tx3);
            glNormal3f(n3.x, n3.y, n3.z);
            glVertex3f(x3, y3, z3);

            float x4 = sin((i + 1) * dtheta) * cos(j * dphi);
            float y4 = sin((i + 1) * dtheta) * sin(j * dphi);
            float z4 = cos((i + 1) * dtheta);
            float tx4 = (i + 1) / float(res);
            float ty4 = j / float(res);
            ofVec3f n4 = ofVec3f(-x4, -y4, -z4);
            glTexCoord2f(ty4, tx4);
            glNormal3f(n4.x, n4.y, n4.z);
            glVertex3f(x4, y4, z4);

            glEnd();
        }
    }
}


#endif /* draw_functions_h */
