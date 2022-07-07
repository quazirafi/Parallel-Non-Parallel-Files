#include "./typos_v.h"
#include "omp.h"
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();

const int BODY_COUNT = N4;

double magnitude(data3D data){
  double squareOfLength = 0.0;
  squareOfLength += data.x * data.x;
  squareOfLength += data.y * data.y;
  squareOfLength += data.z * data.z;
  return sqrt(squareOfLength);
}

void normalize(data3D data){
  double length = magnitude(data);
  data.x = data.x / length;
  data.y = data.y / length;
  data.z = data.z / length;
}

void invert(data3D data) {
  data.x *= -1.0;
  data.y *= -1.0;
  data.z *= -1.0;
}

void direction(data3D fromVector, data3D toVector, data3D resultVector) {
  resultVector.x = toVector.x - fromVector.x;
  resultVector.y = toVector.y - fromVector.y;
  resultVector.z = toVector.z - fromVector.z;
  normalize(resultVector);
}

double forceNewtonianGravity3D(double onMass, double becauseOfMass, data3D onPosition, data3D becauseOfPosition) {
  double deltaX = becauseOfPosition.x - onPosition.x;
  double deltaY = becauseOfPosition.y - onPosition.y;
  double deltaZ = becauseOfPosition.z - onPosition.z;
  double distance = sqrt(deltaX * deltaX + deltaY * deltaY + deltaZ * deltaZ);

  if(distance == 0) {
    return 0;
  }

  double result = G * (onMass * becauseOfMass) /  (distance * distance);
  return result;
}

double computeAccel(double mass, double force ) {
    if( force == 0 ) {
        return 0;
    }

    double result = force / mass;
    return result;
}

double computeVelo(double current, double previous, float deltaT) {
     return previous + (current * deltaT);
}

double computePos(double current, double previous, float deltaT) {
    return previous + (current * deltaT);
}

data3D computeAccel3D(double mass, data3D force) {
    data3D anAccelVector = {0, 0, 0};
    anAccelVector.x = computeAccel(mass, force.x);
    anAccelVector.y = computeAccel(mass, force.y);
    anAccelVector.z = computeAccel(mass, force.z);
    return anAccelVector;
}

data3D computeVelo3D(data3D accel, data3D prevVelo, float deltaT) {
    data3D adoubleVector = {0, 0, 0};
    adoubleVector.x = computeVelo( accel.x, prevVelo.x, deltaT );
    adoubleVector.y = computeVelo( accel.y, prevVelo.y, deltaT );
    adoubleVector.z = computeVelo( accel.z, prevVelo.z, deltaT );
    return adoubleVector;
}

data3D computePos3D(data3D velo, data3D prevPos, float deltaT) 
{
  data3D anPositionVector = {0, 0, 0};
  anPositionVector.x = computePos(velo.x, prevPos.x, deltaT);
  anPositionVector.y = computePos(velo.y, prevPos.y, deltaT);
  anPositionVector.z = computePos(velo.z, prevPos.z, deltaT);
  return anPositionVector;
}

void updateAcceleration(int bodyIndex){
    data3D netForce = { 0, 0, 0 };

							dummyMethod3();
    for(int i = 0; i < BODY_COUNT; i++){
        data3D vectorForceToOther = {0, 0, 0};
        double scalarForceBetween = forceNewtonianGravity3D(mass[bodyIndex], mass[i], position[bodyIndex], position[i]);
        direction(position[bodyIndex], position[i], vectorForceToOther);

        vectorForceToOther.x *= scalarForceBetween;
        vectorForceToOther.y *= scalarForceBetween;
        vectorForceToOther.z *= scalarForceBetween;
        netForce.x += vectorForceToOther.x;
        netForce.y += vectorForceToOther.y;
        netForce.z += vectorForceToOther.z;
    }
							dummyMethod4();

  acceleration[bodyIndex] = computeAccel3D(mass[bodyIndex], netForce);
}

void updateVelocity(int bodyIndex, float deltaT){
    speed[bodyIndex] = computeVelo3D(acceleration[bodyIndex], speed[bodyIndex], deltaT);
}

void updatePosition(int bodyIndex, float deltaT){
    position[bodyIndex] = computePos3D(speed[bodyIndex], position[bodyIndex], deltaT);
}

void displayAll(){
    int index;
							dummyMethod3();
    for(index=0; index < BODY_COUNT; index++) {        
         printf("\nBody %d:\nMassa: %f\nPosiçao(x ,y, z): %f, %f, %f\nVelocidade(x, y, z): %f, %f, %f\nAceleracao(x ,y, z): %f, %f, %f\n\n",
            index + 1, 
            mass[index], 
            position[index].x, position[index].y, position[index].z,
            speed[index].x, speed[index].y, speed[index].z,
            acceleration[index].x, acceleration[index].y, acceleration[index].z);
    }  
							dummyMethod4();
}


void updatePhysics(float deltaT){
    int i;
							dummyMethod1();
    #pragma omp parallel for num_threads(8)
    for(i=0; i < BODY_COUNT; i++) {
        updateAcceleration(i);
        updateVelocity(i, deltaT);
        updatePosition(i, deltaT);        
    }    
							dummyMethod2();
}

void nBodyStart(){
    int j = 0;
    int i = 0;    

							dummyMethod3();
    for (j = 0; j < 1; ++j){
        for (i = 0; i < 10000; ++i){
            updatePhysics(i * 100);
        }
    }
							dummyMethod4();
    //displayAll();
}

int main(){
    nBodyStart();
    return 0;
}
int dummyMethod1(){
    return 0;
}
int dummyMethod2(){
    return 0;
}
int dummyMethod3(){
    return 0;
}
int dummyMethod4(){
    return 0;
}