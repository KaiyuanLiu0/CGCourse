//
// Created by KaiyuanLiu on 2019-05-27.
//

#ifndef GRAPHICS_CAMERA_H
#define GRAPHICS_CAMERA_H

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "../class/map.h"

#include <vector>

struct wall{
	glm::vec3 center;
	double size;
}; 

// defines operations
enum Camera_Movement {
    FORWARD,
    BACKWARD,
    LEFT,
    RIGHT,
    UP,
    DOWN,
    ORBIT
};

// default values
const float YAW         = -90.0f;
const float PITCH       =  0.0f;
const float SPEED       =  2.5f;
const float SENSITIVITY =  0.1f;
const float ZOOM        =  45.0f;


class Camera
{
public:
    glm::vec3 Position;
    glm::vec3 Front;
    glm::vec3 Up;
    glm::vec3 Right;
    glm::vec3 WorldUp;
    float Yaw;
    float Pitch;
    float MovementSpeed;
    float MouseSensitivity;
    float Zoom;
    double width;
    

    Camera(glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f), float yaw = YAW, float pitch = PITCH) : Front(glm::vec3(0.0f, 0.0f, -1.0f)), MovementSpeed(SPEED), MouseSensitivity(SENSITIVITY), Zoom(ZOOM)
    {
        Position = position;
        WorldUp = up;
        Yaw = yaw;
        Pitch = pitch;
        updateCameraVectors();
	width = 0.2;
    }
    // Constructor with scalar values
    Camera(float posX, float posY, float posZ, float upX, float upY, float upZ, float yaw, float pitch) : Front(glm::vec3(0.0f, 0.0f, -1.0f)), MovementSpeed(SPEED), MouseSensitivity(SENSITIVITY), Zoom(ZOOM)
    {
        Position = glm::vec3(posX, posY, posZ);
        WorldUp = glm::vec3(upX, upY, upZ);
        Yaw = yaw;
        Pitch = pitch;
        updateCameraVectors();
    }

    // return view matrix
    // used for lookAt
    glm::mat4 GetViewMatrix()
    {
        return glm::lookAt(Position, Position + Front, Up);
    }

    // keyboard operations, move
    int ProcessKeyboard(Camera_Movement operation, float deltaTime, Map map)
    {
        float velocity = MovementSpeed * deltaTime;
	glm::vec3 front = Front;
	front[1] = 0;
	glm::vec3 right = Right;
	right[1] = 0;
	//glm::vec3 up = Up;
	//up[1] = 0;
	glm::vec3 tmp_ret;
	glm::vec3 stan = {-1, -1, -1};
        if (operation == FORWARD){
	    tmp_ret = col(Position, front * velocity, map);
	    if(tmp_ret == stan){
		return 1;
	    }
            Position += tmp_ret;
	}

        if (operation == BACKWARD){
	    tmp_ret = col(Position, -front * velocity, map);
	    if(tmp_ret == stan){
		return 1;
	    }
            Position += tmp_ret;
	}

        if (operation == LEFT){
	    tmp_ret = col(Position, -right * velocity, map);
	    if(tmp_ret == stan){
		return 1;
	    }
            Position += tmp_ret;
	}

        if (operation == RIGHT){
	    tmp_ret = col(Position, right * velocity, map);
	    if(tmp_ret == stan){
		return 1;
	    }
            Position += tmp_ret;
	}

        if (operation == UP){
	    tmp_ret = col(Position, Up * velocity, map);
	    if(tmp_ret == stan){
		return 1;
	    }
            Position += tmp_ret;
	}
        if (operation == DOWN){
	    tmp_ret = col(Position, -Up * velocity, map);
	    if(tmp_ret == stan){
		return 1;
	    }
            Position += tmp_ret;
	}
        if (operation == ORBIT)
        {
            if (Position.x * Position.x + Position.z * Position.z > 0.1) // divide-by-zero error
            {
                float angularVelocity = MovementSpeed / sqrt(Position.x * Position.x + Position.z * Position.z) * deltaTime;
                float oldX = Position.x;
                float oldZ = Position.z;
                Position.x = oldX * cos(angularVelocity) + oldZ * sin(angularVelocity);
                Position.z = -oldX * sin(angularVelocity) + oldZ * cos(angularVelocity);
            }
        }
	return 0;
    }

    // mouse operations, view direction
    void ProcessMouseMovement(float xoffset, float yoffset, GLboolean constrainPitch = true)
    {
        xoffset *= MouseSensitivity;
        yoffset *= MouseSensitivity;

        Yaw   += xoffset;
        Pitch += yoffset;

        if (constrainPitch)
        {
            if (Pitch > 89.0f)
                Pitch = 89.0f;
            if (Pitch < -89.0f)
                Pitch = -89.0f;
        }

        updateCameraVectors();
    }

    // Processes input received from a mouse scroll-wheel event. Only requires input on the vertical wheel-axis
    void ProcessMouseScroll(float yoffset)
    {
        if (Zoom >= 1.0f && Zoom <= 45.0f)
            Zoom -= yoffset;
        if (Zoom <= 1.0f)
            Zoom = 1.0f;
        if (Zoom >= 45.0f)
            Zoom = 45.0f;
    }

private:
    // calculate
    void updateCameraVectors()
    {
        // new front vector
        glm::vec3 front;
        front.x = cos(glm::radians(Yaw)) * cos(glm::radians(Pitch));
        front.y = sin(glm::radians(Pitch));
        front.z = sin(glm::radians(Yaw)) * cos(glm::radians(Pitch));
        // normalized
        Front = glm::normalize(front);
        // new right and up
        Right = glm::normalize(glm::cross(Front, WorldUp));
        Up    = glm::normalize(glm::cross(Right, Front));
    }

    int isin(glm::vec3 pos, glm::vec3 per, Map map){
	//for(int i = 0; i < 3; i++){
		int pos0_1 = int(pos[0] + per[0]+ 0.3);
		int pos0_2 = int(pos[0] + per[0]+ 0.7);
		//pos[1] = int(pos[1] + per[1]);
		int pos2_1 = int(pos[2] + per[2] + 0.3);
		int pos2_2 = int(pos[2] + per[2] + 0.7);
		//std::cout << pos[0] << pos[1] << pos[2] << std::endl;
		if(pos[1] + per[1] > 0.7){
			return 1;
		}
		if(pos[1] + per[1] < 0){
			return 0;
		}
		int tmp_0 = int(pos[0] + per[0]+ 0.5);
		int tmp_1 = int(pos[2] + per[2]+ 0.5);
		if(tmp_0 > map.GetLimit() / 2 - 3 && tmp_0 < map.GetLimit() / 2 + 3 && 
		   tmp_1 > map.GetLimit() / 2 - 3 && tmp_1 < map.GetLimit() / 2 + 3){
			return 2;
		}
		if(map.GetType(pos0_1, pos2_1) == WALL || 
		   map.GetType(pos0_1, pos2_2) == WALL || 
		   map.GetType(pos0_2, pos2_1) == WALL || 	
		   map.GetType(pos0_2, pos2_2) == WALL
		)
			//std::cout << "WALL!" << std::endl;
			return 0;
		/*if(pos[i] + per[i] > input.center[i] + input.size + width || pos[i] + per[i] < input.center[i] - input.size - width){
			return -1;
		}*/
	//}
	return 1;
    }

    glm::vec3 col(glm::vec3 pos, glm::vec3 per, Map map){
        //std::cout << pos[0] << pos[1] << pos[2] << std::endl;
	int abs_direct;
	//for(int i = 0; i < walls->size(); i++){
		int ret = isin(pos, per, map);
		if(ret == 2){
			return {-1, -1, -1};
		}
		if(isin(pos, per, map) == 0){
			return {0, 0, 0};
		}
	//}
	return per;
    }
};
#endif //GRAPHICS_CAMERA_H
