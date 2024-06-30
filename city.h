//
//  city.h
//  ProjetoCG_Tiago_Almeida_2021221615
//
//  Created by Tiago Almeida.
//


// Header guard to prevent multiple inclusion
#ifndef city_h
#define city_h

// Function to construct the city skyline
inline void city(std::vector<int> color_list, std::vector<int> floors_list, bool flag, float lift, ofImage texture) {
    // Initial coordinates for building placement
    float building_coordX = -gw() * 0.5 + gw() * 1.5 / 40;
    float building_coordY = -gh() * 0.5 + gh() * 1.5 / 20;

    // Step size for building placement
    float stepX = gw() / 40 + gw() * 1.5 / 40 * 2;
    float stepY = gh() / 20 + gh() * 1.5 / 20 * 2;

    // Variables for elevator animation
    float countElevator = 0, elevator;

    // Constants for building height calculation
    int height_base = 50, height;

    // Loop through rows and columns to construct the city
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 10; j++) {
            int num = j + i * 5;

            // Check if the current position is not in the middle of the city
            if (!(i == 2 && (j == 4 || j == 5))) {
                // Set building color based on the color list
                switch (color_list[num]) {
                    case 1:
                        glColor3f(1, 0, 0); // Red
                        break;
                    case 2:
                        glColor3f(.5, .5, 0); // Olive
                        break;
                    case 3:
                        glColor3f(1, .5, 0); // Orange
                        break;
                    case 4:
                        glColor3f(.5, 0, .5); // Purple
                        break;
                    case 5:
                        glColor3f(1, .5, .5); // Light Pink
                        break;
                    case 6:
                        glColor3f(1, 0, 1); // Magenta
                        break;
                    case 7:
                        glColor3f(1, 1, 1); // White
                        break;
                    case 8:
                        glColor3f(.5, 1, .5); // Light Green
                        break;
                    case 9:
                        glColor3f(1, 0, 1); // Magenta
                        break;
                }

                // Calculate building height based on the floors list
                height = height_base * floors_list[num];

                // Translate, scale, and draw the building
                glPushMatrix();
                glTranslatef(building_coordX, building_coordY, height * 0.5);
                glScalef(gw() * 3 / 40, gh() * 3 / 20, height);

                // Check if the building is a cube or a mesh
                if (j % 2 == 0 || i % 2 != 0) {
                    // Draw the building as a cube
                    building_cube();
                    glPopMatrix();

                    // Draw the elevator and cube on top of the building
                    glPushMatrix();
                    glColor3f(1, 1, 1);

                    // Construct the elevator in the Cube Building
                    if (flag == true && lift >= height) {
                        glTranslatef(building_coordX, building_coordY, height - 7.5);
                    } else if (flag == true && lift < height) {
                        glTranslatef(building_coordX, building_coordY, lift - 7.5);
                    } else if (flag == false && lift <= 0) {
                        glTranslatef(building_coordX, building_coordY, 0 + 7.5);
                    } else if (flag == false && lift > 0 && lift <= height) {
                        glTranslatef(building_coordX, building_coordY, lift - 7.5);
                    } else if (flag == false && lift > 0 && lift > height) {
                        glTranslatef(building_coordX, building_coordY, height - 7.5);
                    }

                    glScalef(10, 10, 10);
                    // Draw the cube on top of the building
                    building_cube();
                    glPopMatrix();
                } else {
                    // Draw the building as a mesh
                    building_mesh(10, 5, texture);
                    glPopMatrix();
                }
            }
            // Move to the next column
            building_coordX += stepX;
        }
        // Move to the next row
        building_coordY += stepY;
        // Reset X coordinate for the next row
        building_coordX = -gw() * 0.5 + gw() * 1.5 / 40;
    }
}

#endif /* city_h */
