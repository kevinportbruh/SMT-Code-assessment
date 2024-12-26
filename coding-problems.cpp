#include "coding-problems.h"
#include <iostream>
#include <limits>
#include <cmath>
//@Author: Kevin Portillo Self-Proclaimed Coding Wizard
//first problem
bool FindCameraHeight(const double field_length, const double camera_field_of_view, double &camera_height){
    /** Feel free to minimize this comment, I explain my thought process here
     * At first glance, this problem is a trigonometry problem where we are solving for an unknown side of a triangle.
     * We have a base field length, we have a camera FOV which is given in degrees.
     * We have to find heigh H, which is assumed to always be pointed directly at the center of the field.
     * We also know the missing angle due to the angle sum property of a triangle. (sum of all internal angles == 180)
     * We should split the length of the field in half, as well as the FOV, and turn the triangle into a right triangle.
     * ------------------------------
     * If we use the formula  tangent(0) =Opp/Adj (0 being the degree we found mathematically, Opp being H, and Adj being L/2) 
     * we can rearrange to Adj = tan(0) * Opp -> H = tan(0) *(L/2)
     * 
     * set H to the cam_height param. and return true if all successful OR RETURN FALSE if we have any illegal fields.
     */
    
    //input validation b4 computations
    if(field_length <= 0){
        //negative & 0 field lengths are not possible
        std::cout << "invalid input, field length cannot be <= 0 and is: "<< field_length << std::endl;
        return false;
    }
    if(camera_field_of_view <= 0 || camera_field_of_view >= 180){
        // and FOV must be between 0 and 180, exclusive.
        std::cout << "invalid input, camera FOV must be between (0,180) and is: " << camera_field_of_view << std::endl;
        return false;
    }
    
    //split field in half aswell as the FOV to get our right triangle
    double L = field_length/2; 
    std::cout << "L/2: " << L << std::endl;
    double halfFOV = camera_field_of_view/2;
    std::cout << "half FOV: " << halfFOV << std::endl;
    double theta = 90 - halfFOV; //Camera height is opposite of this angle, while L/2 is adjacent
    std::cout << "interior angle: " << theta << std::endl;
    //turn theta into radians
    theta = theta * (M_PI/180);
    camera_height = tan(theta) * L;
    
    return true;
};
//second problem
bool FindIntersectionDistance(const double camera_height, const double camera_tilt, double &distance){
    /**
     * I believe this is another triangle problem. We want to find the distance from the origin to the intersection point
     * the intersection point is where the camera is looking at on the ground plane.
     * we are given the height of the camera, and its tilt from the horizion.
     * if the camera is positioned above the origion, then the projection line down to the ground will be the hypotenuse of a right triangle.
     * We need to determin the interior angle of the triangle to find the distance from the origin to the intersection point.
     * 
     * The camera can only be tiled down between (0,90) exclusively.
     * we flip the tilt of the camera to get the interior angle of the triangle. (subtract 90 from the tilt)
     * we can use the formula tan(0) = Opp/Adj to find the distance from the origin to the intersection point.
     * where opp is the camera height and adj is the distance we are looking for.
     * -----
     * Tan(0) = Opp/Adj -> Adj = Opp*tan(0) -> distance = camera_height*tan(90-camera_tilt)
     */

    //input validation
    if(camera_height <= 0){
        //negative & 0 camera heights are not possible
        std::cout << "invalid input, camera height cannot be <= 0 and is: "<< camera_height << std::endl;
        return false;
    }else if(camera_tilt <= 0 || camera_tilt >= 90){
        //camera tilt must be between 0 and 90, exclusive
        std::cout << "invalid input, camera tilt must be between (0,90) and is: " << camera_tilt << std::endl;
        return false;
    }
    //all clear
    double theta = 90 - camera_tilt; //flip the tilt to get the interior angle of the triangle (i.e if the tilt down is 30 degrees, the interior angle is 60)
    std::cout << "interior angle: " << theta << std::endl;
    theta = theta * (M_PI/180); //convert to radians
    distance = camera_height*tan(theta); //find the distance from the origin to the intersection point
    
    return true;
};
//third problem
bool IsHomeRun(const double exit_velocity, const double launch_angle, const double wall_height, bool &is_homerun){
    /**
     * This is a physics problem, we have to find if the batter will hit a home run.
     * We are given the exit velocity of the ball, the launch angle, and the height of the outfield wall.
     * The wall is always 400 units away from the batter, and the ball is always hit 3 units off the ground.
     * The ball has a constant downward force of 32.2 units per second squared (gravity).
     * if Y is the height of the ball after traveling the 400 units then we just have to compare
     * y > wall_height to see if the ball will be a home run.
     * 
     * after a bit of research, I found the formula for projectile motion which is:
     * y= y0 + v0y*t - 1/2 *g*t^2
     * where:
     * y0 is intial height
     * v0 is initial velocity (with x and y components) 
     * v0y vertical compoenet of velocity (v0y = v0 * sin(launch_angle))
     * v0x horizontal component of velocity (v0x = v0 * cos(launch_angle))
     * g is gravity constant
     * 
     * we need to solve for t to find the height of the ball after traveling 400 units
     * if x is the distance traveled at time t while moving at v0x, 
     *      then x = v0x * t -> t = x/v0x
     * since the distance we are looking for is always 400 we get:
     *      t= 400/v0x
    
     * if we plug everything in correctly we should get the height of ball at time t (after it has traveled 400 units)
     * so if that output is > wall_height then we set is_homerun to true and return true
     * else we set is_homerun to false and return true (since we have valid inputs)
    */

    //invalid inputs
    //negative exit velocity is not possible and 0 is not possible, the launch angle must be between 0 and 90 or else you are hitting the ball into the ground or straight up.
    //the wall height must be > 0
    if(exit_velocity <= 0){
        std::cout << "invalid input, exit velocity cannot be <= 0 and is: "<< exit_velocity << std::endl;
        return false;
    }else if(launch_angle <= 0 || launch_angle >= 90){
        std::cout << "invalid input, launch angle must be between (0,90) (exclusively) and is: " << launch_angle << std::endl;
        return false;
    }else if(wall_height <= 0){
        std::cout << "invalid input, wall height cannot be <= 0 and is: "<< wall_height << std::endl;
        return false;
    }


    //constants for the problem
    //gravity, distance to wall, initial height of ball
    const double g = 32.2; 
    const double distanceToWall = 400; 
    const double initialHeight = 3; 

    //convert launch angle to radians
    double theta = launch_angle * (M_PI/180); 
    //get the x and y components of the velocity
    double velY = exit_velocity * sin(theta); //vertical component
    std::cout << "vertical component: " << velY << std::endl;
    double velX = exit_velocity * cos(theta);//horizontal component
    std::cout << "horizontal component: " << velX << std::endl;

    //find the time it takes to travel 400 units
    double time = distanceToWall/velX;
    std::cout << "time taken to travel 400ft: " << time << std::endl;


    double ballAt400ft = initialHeight + velY*time - 0.5 * g * pow(time,2); 
    std::cout << "ball at 400ft: " << ballAt400ft << std::endl;
    //if the ball is higher than the wall then it is a home run
    ballAt400ft > wall_height ? is_homerun = true : is_homerun = false;
    return true;//no matter if we hit home run or not we had valid inputs.


};

int main(){
    //menu to quickly test functions
    bool quit = false;
    int choice =-1;
    while(!quit){
        std::cout << "Choose a problem to solve: " << std::endl;
        std::cout << "1. Find Camera Height\n2. Find Intersection Distance\n3. Is Home Run\n4. Quit" << std::endl;

        std::cin >> choice;

        // Handle invalid input
        if (std::cin.fail()) {
            std::cin.clear(); // Clear the error flag
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Discard invalid input
            std::cout << "Invalid input. Please enter a number.\n";
            continue;
        }


        switch(choice){
            case 1 :
                double fieldL, camFOV;
                double camera_height; //output, if invalid inputs this will stay min double
                std::cout << "Enter field length: ";
                std::cin >> fieldL;
                std::cout << "Enter camera FOV: ";
                std::cin >> camFOV;
                if(FindCameraHeight(fieldL, camFOV, camera_height)){
                    std::cout << "the camera should be placed at: " << camera_height << " units high to cover the entire field" << std::endl;
                }else{
                    std::cout << "Invalid inputs" << std::endl;
                }
                
                break;
            case 2:
                double cam_height, cam_tilt;
                double dist; //output, if invalid inputs this will stay min double
                std::cout << "Enter camera height: ";
                std::cin >> cam_height;
                std::cout << "Enter camera tilt: ";
                std::cin >> cam_tilt;
                if(FindIntersectionDistance(cam_height, cam_tilt, dist)){
                    std::cout << "The distance from the origin to the intersection is: "<< dist << " units long" << std::endl;
                }else{
                    std::cout << "Invalid inputs" << std::endl;
                }
                break;
            case 3:
                double exit_vel, launch_ang, wall_height;
                bool is_homerun; //output, if invalid inputs this will stay false
                std::cout << "Enter exit velocity: ";
                std::cin >> exit_vel;
                std::cout << "Enter launch angle: ";
                std::cin >> launch_ang;
                std::cout << "Enter wall height: ";
                std::cin >> wall_height;
                if(IsHomeRun(exit_vel, launch_ang, wall_height, is_homerun)){
                    std::cout << "Home Run? " << (is_homerun ? "Yes" : "No") << std::endl;
                }else{
                    std::cout << "Invalid inputs" << std::endl;
                }
                
                break;
            case 4:
                quit = true;
                break;
            default:
                std::cout << "Invalid choice, try again" << std::endl;
                break;
        };


    }

   /**
    * got tired of recompiling to test functions so I made a menu to test them
    * these were some of the numbers I used to test.
    *  double camera_height;
    FindCameraHeight(300, 90, camera_height);
    std::cout << camera_height << std::endl;
    double distance;
    FindIntersectionDistance(300, 1, distance);
    std::cout << distance << std::endl;

    bool is_homerun;
    IsHomeRun(115, 50, 10, is_homerun);
    std::cout << is_homerun << std::endl;
    */
   

    return 0;
};
