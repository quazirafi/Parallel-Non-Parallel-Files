#include<stdio.h>
#include<stdlib.h>
#include "omp.h"
#include <time.h>
#include <math.h>
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();

#define NBIM 200
#define NBLIGNE 1080
#define NBCOL 1080
#define NBPROCS 4

char video[NBIM][NBLIGNE][NBCOL];
char videoseuil[NBIM][NBLIGNE][NBCOL];
char videoseuilOld[NBLIGNE][NBCOL];
char videoDiff[NBIM][NBLIGNE][NBCOL];
char videoDiffErod[NBIM][NBLIGNE][NBCOL];
int videoSil[NBIM][NBLIGNE][NBCOL];



int main (void){

    int ncores;

    int i,j,k;
    int seuil = 15;
    int compteur = 0;
    int zoneDetect;
    double start, end, timep, times;
    ncores = omp_get_num_procs();
    printf("%d coeurs disponibles\n",ncores);

//version sequentielle

    //initialisations

							dummyMethod3();
    for(i=0;i<NBIM;i++){
        for(j=0;j<NBLIGNE;j++){
            for(k=0;k<NBCOL;k++){
                video[i][j][k]=(i+j+k)%255;
                videoDiff[i][j][k] = 0;
                videoDiffErod[i][j][k] = 0;
                videoSil[i][j][k]= 0;
                videoseuil[i][j][k]=0 ;
            }
        }
    }
							dummyMethod4();


							dummyMethod3();
    for(j=0;j<NBLIGNE;j++){
        for(k=0;k<NBCOL;k++){
            videoseuilOld[j][k]=0;
        }
    }
							dummyMethod4();

    start=omp_get_wtime();
    //etape 1 seuillage

							dummyMethod3();
    for(i=0;i<NBIM;i++){
        for(j=0;j<NBLIGNE;j++){
            for(k=0;k<NBCOL;k++){
                if(video[i][j][k]<seuil)
                    videoseuil[i][j][k] = 0;
                else
                    videoseuil[i][j][k] = 1;
                    }}}
							dummyMethod4();

    //etape 2 comparaison

							dummyMethod3();
    for(i=0;i<NBIM;i++){

        for(j=0;j<NBLIGNE;j++){
            for(k=0;k<NBCOL;k++){
                if(videoseuil[i][j][k] != videoseuilOld[j][k])
                    videoDiff[i][j][k] = 1;
                else
                    videoDiff[i][j][k] = 0;
                videoseuilOld[j][k] = videoseuil[i][j][k];
            }}}
							dummyMethod4();

    //etape 3 erosion horizontale

							dummyMethod3();
    for(i=0;i<NBIM;i++){
        for(j=0;j<NBLIGNE;j++){
            for(k=0;k<NBCOL;k++){
                if (k==0){
                    if (videoDiff[i][j][1]==1 && videoDiff[i][j][0]==1)
                        videoDiffErod[i][j][k]=1;
                    else
                        videoDiffErod[i][j][k]=0;
                } else
                if (k==NBCOL-1){
                    if (videoDiff[i][j][NBCOL-1]==1 && videoDiff[i][j][NBCOL-2]==1)
                        videoDiffErod[i][j][NBCOL-1]=1;
                    else
                        videoDiffErod[i][j][NBCOL-1]=0;
                }else
                if(videoDiff[i][j][k-1]==1 && videoDiff[i][j][k]==1 && videoDiff[i][j][k+1]==1)
                    videoDiffErod[i][j][k]=1;
                else
                    videoDiffErod[i][j][k]=0;

            }}}
							dummyMethod4();

    //etape 4 silhouette horizontale

							dummyMethod3();
    for(i=0;i<NBIM;i++){
            for(j=0;j<NBLIGNE;j++){
                zoneDetect =0;
                for(k=0;k<NBCOL;k++){
                    if(!zoneDetect)
                        if(videoDiffErod[i][j][k]==1)  {
                            videoSil[i][j][k] =1;
                            zoneDetect = 1;}
                        else{
                            videoSil[i][j][k] =0;
                        }
                    else
                        {
                        if(videoDiffErod[i][j][k]==0)  {
                            videoSil[i][j][k] =1;
                            zoneDetect = 0;}
                        else{
                            videoSil[i][j][k] =0;
                        }
                    }
                }}}
							dummyMethod4();
    end=omp_get_wtime();

    //utilisation des resultats

							dummyMethod3();
    for(i=0;i<NBIM;i++){
            for(j=0;j<NBLIGNE;j++){
                for(k=0;k<NBCOL;k++){
                        compteur+= videoSil[i][j][k];}}}
							dummyMethod4();
    printf("*******************************************\n");
    printf("Version sequentielle\n");
    printf ("res : %d \n",compteur);
    compteur =0;
    times=(end-start);
    printf ("temps d'execution seq: %g \n",times);

    /*********************************************/
							dummyMethod3();
    for(i=0;i<NBIM;i++){
        for(j=0;j<NBLIGNE;j++){
            for(k=0;k<NBCOL;k++){
                video[i][j][k]=(i+j+k)%255;
                videoDiff[i][j][k] = 0;
                videoDiffErod[i][j][k] = 0;
                videoSil[i][j][k]= 0;
                videoseuil[i][j][k]=0 ;
            }
        }
    }
							dummyMethod4();

							dummyMethod3();
    for(j=0;j<NBLIGNE;j++){
        for(k=0;k<NBCOL;k++){
            videoseuilOld[j][k]=0;
        }
    }
							dummyMethod4();

    start=omp_get_wtime();
    //etape 1 seuillage
							dummyMethod1();
    #pragma omp parallel for num_threads(4) private(i,j,k)
    for(i=0;i<NBIM;i++){
        for(j=0;j<NBLIGNE;j++){
            for(k=0;k<NBCOL;k++){
                if(video[i][j][k]<seuil)
                    videoseuil[i][j][k] = 0;
                else
                    videoseuil[i][j][k] = 1;
                    }}}
							dummyMethod2();

    //etape 2 comparaison
    for(i=0;i<NBIM;i++){
															dummyMethod1();
        #pragma omp parallel for num_threads(4) private(j,k)
        for(j=0;j<NBLIGNE;j++){
            for(k=0;k<NBCOL;k++){
                if(videoseuil[i][j][k] != videoseuilOld[j][k])
                    videoDiff[i][j][k] = 1;
                else
                    videoDiff[i][j][k] = 0;
                videoseuilOld[j][k] = videoseuil[i][j][k];
            }}}
															dummyMethod2();

    //etape 3 erosion horizontale
							dummyMethod1();
    #pragma omp parallel for num_threads(4) private(i,j,k)
    for(i=0;i<NBIM;i++){
        for(j=0;j<NBLIGNE;j++){
            for(k=0;k<NBCOL;k++){
                if (k==0){
                    if (videoDiff[i][j][1]==1 && videoDiff[i][j][0]==1)
                        videoDiffErod[i][j][k]=1;
                    else
                        videoDiffErod[i][j][k]=0;
                } else
                if (k==NBCOL-1){
                    if (videoDiff[i][j][NBCOL-1]==1 && videoDiff[i][j][NBCOL-2]==1)
                        videoDiffErod[i][j][NBCOL-1]=1;
                    else
                        videoDiffErod[i][j][NBCOL-1]=0;
                }else
                if(videoDiff[i][j][k-1]==1 && videoDiff[i][j][k]==1 && videoDiff[i][j][k+1]==1)
                    videoDiffErod[i][j][k]=1;
                else
                    videoDiffErod[i][j][k]=0;

            }}}
							dummyMethod2();

    //etape 4 silhouette horizontale
							dummyMethod1();
    #pragma omp parallel for num_threads(4) private(i,j,k,zoneDetect)
    for(i=0;i<NBIM;i++){
            for(j=0;j<NBLIGNE;j++){
                zoneDetect =0;
                for(k=0;k<NBCOL;k++){
                    if(!zoneDetect)
                        if(videoDiffErod[i][j][k]==1)  {
                            videoSil[i][j][k] =1;
                            zoneDetect = 1;}
                        else{
                            videoSil[i][j][k] =0;
                        }
                    else
                        {
                        if(videoDiffErod[i][j][k]==0)  {
                            videoSil[i][j][k] =1;
                            zoneDetect = 0;}
                        else{
                            videoSil[i][j][k] =0;
                        }
                    }
                }}}
							dummyMethod2();
    end=omp_get_wtime();

    //utilisation des resultats
    for(i=0;i<NBIM;i++){
            for(j=0;j<NBLIGNE;j++){
                for(k=0;k<NBCOL;k++){
                        compteur+= videoSil[i][j][k];}}}


    timep=(end-start);
    printf("*******************************************\n");
    printf("Version parallele 4 threads\n");
    printf ("res : %d \n",compteur);
    printf ("temps d'execution par: %g \n",timep);
    printf ("Acceleration : %g\n",times/timep);
    printf ("Efficactite : %g\n",(times/timep)/4);
    compteur =0;
    printf("*******************************************\n");
    /*********************************************/

    for(i=0;i<NBIM;i++){
        for(j=0;j<NBLIGNE;j++){
            for(k=0;k<NBCOL;k++){
                video[i][j][k]=(i+j+k)%255;
                videoDiff[i][j][k] = 0;
                videoDiffErod[i][j][k] = 0;
                videoSil[i][j][k]= 0;
                videoseuil[i][j][k]=0 ;
            }
        }
    }

    for(j=0;j<NBLIGNE;j++){
        for(k=0;k<NBCOL;k++){
            videoseuilOld[j][k]=0;
        }
    }

    start=omp_get_wtime();
    //etape 1 seuillage
							dummyMethod1();
    #pragma omp parallel for num_threads(6) private(i,j,k)
    for(i=0;i<NBIM;i++){
        for(j=0;j<NBLIGNE;j++){
            for(k=0;k<NBCOL;k++){
                if(video[i][j][k]<seuil)
                    videoseuil[i][j][k] = 0;
                else
                    videoseuil[i][j][k] = 1;
                    }}}
							dummyMethod2();

    //etape 2 comparaison
    for(i=0;i<NBIM;i++){
															dummyMethod1();
        #pragma omp parallel for num_threads(6) private(j,k)
        for(j=0;j<NBLIGNE;j++){
            for(k=0;k<NBCOL;k++){
                if(videoseuil[i][j][k] != videoseuilOld[j][k])
                    videoDiff[i][j][k] = 1;
                else
                    videoDiff[i][j][k] = 0;
                videoseuilOld[j][k] = videoseuil[i][j][k];
            }}}
															dummyMethod2();

    //etape 3 erosion horizontale
							dummyMethod1();
    #pragma omp parallel for num_threads(6) private(i,j,k)
    for(i=0;i<NBIM;i++){
        for(j=0;j<NBLIGNE;j++){
            for(k=0;k<NBCOL;k++){
                if (k==0){
                    if (videoDiff[i][j][1]==1 && videoDiff[i][j][0]==1)
                        videoDiffErod[i][j][k]=1;
                    else
                        videoDiffErod[i][j][k]=0;
                } else
                if (k==NBCOL-1){
                    if (videoDiff[i][j][NBCOL-1]==1 && videoDiff[i][j][NBCOL-2]==1)
                        videoDiffErod[i][j][NBCOL-1]=1;
                    else
                        videoDiffErod[i][j][NBCOL-1]=0;
                }else
                if(videoDiff[i][j][k-1]==1 && videoDiff[i][j][k]==1 && videoDiff[i][j][k+1]==1)
                    videoDiffErod[i][j][k]=1;
                else
                    videoDiffErod[i][j][k]=0;

            }}}
							dummyMethod2();

    //etape 4 silhouette horizontale
							dummyMethod1();
    #pragma omp parallel for num_threads(6) private(i,j,k,zoneDetect)
    for(i=0;i<NBIM;i++){
            for(j=0;j<NBLIGNE;j++){
                zoneDetect =0;
                for(k=0;k<NBCOL;k++){
                    if(!zoneDetect)
                        if(videoDiffErod[i][j][k]==1)  {
                            videoSil[i][j][k] =1;
                            zoneDetect = 1;}
                        else{
                            videoSil[i][j][k] =0;
                        }
                    else
                        {
                        if(videoDiffErod[i][j][k]==0)  {
                            videoSil[i][j][k] =1;
                            zoneDetect = 0;}
                        else{
                            videoSil[i][j][k] =0;
                        }
                    }
                }}}
							dummyMethod2();
    end=omp_get_wtime();

    //utilisation des resultats
    for(i=0;i<NBIM;i++){
            for(j=0;j<NBLIGNE;j++){
                for(k=0;k<NBCOL;k++){
                        compteur+= videoSil[i][j][k];}}}
    timep=(end-start);
    printf("Version parallele 6 threads\n");
    printf("res : %d \n",compteur);
    printf ("temps d'execution par: %g \n",timep);
    printf ("Acceleration : %g\n",times/timep);
    printf ("Efficactite : %g\n",(times/timep)/6);
    compteur=0;
   /********************************************************/
    //initialisations
    for(i=0;i<NBIM;i++){
        for(j=0;j<NBLIGNE;j++){
            for(k=0;k<NBCOL;k++){
                    video[i][j][k]=(i+j+k)%255;
                    videoDiff[i][j][k] = 0;
                    videoDiffErod[i][j][k] = 0;
                    videoSil[i][j][k]= 0;
                    videoseuil[i][j][k]=0 ;
    }}}

    for(j=0;j<NBLIGNE;j++){
                for(k=0;k<NBCOL;k++){
                    videoseuilOld[j][k]=0;
    }}

    start=omp_get_wtime();
    int num1, num2, num3;

    #pragma omp parallel sections num_threads(4) shared(num1,num2,num3) private(i,j,k,zoneDetect) //manque q3+q4+q5 (q5 : voir TD partie 3)
    {

        //etape 1 seuillage
        #pragma omp section
        {
            num1=0;
            for(i=0;i<NBIM;i++){
            //startEtage[1] = omp_get_wtime(); si mins = 0 ne pas être surpris
                for(j=0;j<NBLIGNE;j++){
                    for(k=0;k<NBCOL;k++){
                        if(video[i][j][k]<seuil)
                            videoseuil[i][j][k] = 0;
                        else
                            videoseuil[i][j][k] = 1;
                            }}
            //endEtage[1] = omp_get_wtime();
            #pragma omp critical(s1)
                num1++;
            }
        }

        //etape 2 comparaison
        #pragma omp section
        {
            num2 = 0;
            int attente;
            for(i=0;i<NBIM;i++){
                do{
                    #pragma omp critical(s1)
                        attente = (num1 <= i);
                } while(attente);
                //startEtage[2] = omp_get_wtime();
                for(j=0;j<NBLIGNE;j++){
                    for(k=0;k<NBCOL;k++){
                        if(videoseuil[i][j][k] != videoseuilOld[j][k])
                            videoDiff[i][j][k] = 1;
                        else
                            videoDiff[i][j][k] = 0;
                        videoseuilOld[j][k] = videoseuil[i][j][k];
                    }}
            //endEtage[2] = omp_get_wtime();
            #pragma omp critical(s2)
                num2++;
            }
        }

        //etape 3 erosion horizontale
        #pragma omp section
        {
            num3 = 0;
            int attente;
            for(i=0;i<NBIM;i++){
                do{
                    #pragma omp critical(s2)
                        attente = (num2 <= i);
                } while(attente);
                for(j=0;j<NBLIGNE;j++){
                    for(k=0;k<NBCOL;k++){
                        if (k==0){
                            if (videoDiff[i][j][1]==1 && videoDiff[i][j][0]==1)
                                videoDiffErod[i][j][k]=1;
                            else
                                videoDiffErod[i][j][k]=0;
                        } else
                        if (k==NBCOL-1){
                            if (videoDiff[i][j][NBCOL-1]==1 && videoDiff[i][j][NBCOL-2]==1)
                                videoDiffErod[i][j][NBCOL-1]=1;
                            else
                                videoDiffErod[i][j][NBCOL-1]=0;
                        }else
                        if(videoDiff[i][j][k-1]==1 && videoDiff[i][j][k]==1 && videoDiff[i][j][k+1]==1)
                            videoDiffErod[i][j][k]=1;
                        else
                            videoDiffErod[i][j][k]=0;
                    }}
            #pragma omp critical(s3)
                num3++;
            }

        }

        //etape 4 silhouette horizontale
        #pragma omp section
        {
            int attente;
            for(i=0;i<NBIM;i++){
                do{
                    #pragma omp critical(s3)
                        attente = (num3 <= i);
                } while(attente);
                    for(j=0;j<NBLIGNE;j++){
                        zoneDetect =0;
                        for(k=0;k<NBCOL;k++){
                            if(!zoneDetect)
                                if(videoDiffErod[i][j][k]==1)  {
                                    videoSil[i][j][k] =1;
                                    zoneDetect = 1;}
                                else{
                                    videoSil[i][j][k] =0;
                                }
                            else
                                {
                                if(videoDiffErod[i][j][k]==0)  {
                                    videoSil[i][j][k] =1;
                                    zoneDetect = 0;}
                                else{
                                    videoSil[i][j][k] =0;
                                }
                            }
                        }}}
        }
    }

    end=omp_get_wtime();
    printf("*******************************************\n");
    printf("Version parallele flux\n");
    for(i=0;i<NBIM;i++){
            for(j=0;j<NBLIGNE;j++){
                for(k=0;k<NBCOL;k++){
                        compteur+= videoSil[i][j][k];}}}
    printf ("res : %d \n",compteur);
    compteur =0;
    timep=(end-start);

    printf ("temps d'execution: %g \n",timep);
    printf("acceleration : %g \n", times/timep);
    printf("efficacite : %g \n",(times/timep)/ncores);

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