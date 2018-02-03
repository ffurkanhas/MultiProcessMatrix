#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#define KOLTUK 5
#define BERBER 1

void *berber(void *args);
void *musteri(void *args);

int musteri_sayisi;
sem_t koltuk_mutex;
sem_t sem_berber;
sem_t sem_musteri;
int koltuk_sayac = KOLTUK;
int toplam_zaman = 0;

int main(){
		srand ((unsigned)time(NULL));
		int i;
		printf("Musteri sayisini giriniz: ");
		scanf("%d",&musteri_sayisi);

		pthread_t berber_thread;
		pthread_t musteriler[musteri_sayisi];

		sem_init(&koltuk_mutex,0,1);
   		sem_init(&sem_musteri,0,0);
		sem_init(&sem_berber,0,0);

		pthread_create(&berber_thread, NULL, berber, NULL); //1 tane berber

		for (i = 0; i < musteri_sayisi; i++){
	    	pthread_create(&musteriler[i], NULL, musteri, NULL);
		}

		while(musteri_sayisi > 0){

		}
		printf("Tiras bitti %d saniye surdu\n",toplam_zaman);

}

void *berber(void *args){
	int berber_zaman;
	printf("Berber olusturuldu\n");
	while(1){
		sem_wait(&sem_musteri); //musteri gelmesini bekle
		sem_wait(&koltuk_mutex); //bos koltuk bekle
		sem_post(&sem_berber); //sinyal gonderdik
		sem_post(&koltuk_mutex);
		koltuk_sayac += 1; //koltuk sayisi +1
		printf("Berber tirasa basladi...\n");
		berber_zaman = (rand() % 3) + 1;
		sleep(berber_zaman);
		toplam_zaman += berber_zaman;
		printf("Berber tirasi bitirdi %d saniye surdu ve %d musteri kaldi\n",berber_zaman,musteri_sayisi);
	}
	
}

void *musteri(void *args){
	int musteri_zaman;

	while(1){
		sem_wait(&koltuk_mutex); //koltuk bekle
		if(koltuk_sayac <= 0){ //koltuk yoksa disari cik dolas
		   sem_post(&koltuk_mutex);
		}
		else{
			koltuk_sayac -= 1;
			sem_post(&sem_musteri);
		    sem_post(&koltuk_mutex);
			sem_wait(&sem_berber);
			musteri_sayisi--;
		}
		musteri_zaman = (rand() % 3) + 1;
		sleep(musteri_zaman);
	}

}