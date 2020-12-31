#include<stdio.h>
#include<stdlib.h>
#include<time.h>


int w[7] = { 0,2,10,13,17,22,42 };
int W = 52;

int promising(int i, int weight, int total); //노드가 유망한지 확인하는 함수
int estimate_sumofsubset(int n); //Montecarlo 기법으로 수행시간의 추정치를 계산하는 함수

int main(void) {
	printf("모든 해를 찾기 위해 검사하는 노드의 총 개수 추정치들의 합-> %u", estimate_sumofsubset(6)); //숫자 6개

	return 0;
}


// 노드가 promising한지 검사하는 함수
int promising(int i, int weight, int total) {
	if ((weight + total >= W) && (weight == W || weight + w[i + 1] <= W))
		return 1; //promising한 경우 1을 리턴
	else
		return 0; //nonpromising한 경우 0을 리턴
}


//Montecarlo 기법으로 수행시간의 추정치를 계산하는 함수
int estimate_sumofsubset(int n) {

	int m, t, i, mprod, numnodes, nextselect, numans, count_m1, count_m2;
	int weight = 0; int total = 106; int W = 52; int totalnumnodes = 0;
	int numanswer = 0; //찾은 해의 개수
	int ans_node = 0; //찾은 해의 노드 개수 추정치

	m = 1; //뿌리의 유망한 자식 2개
	t = 2; //노드의 자식
	i = 0;
	mprod = 1;
	numnodes = 1;
	numans = 0;

	srand(time(NULL));

	while (numanswer != 2) { //모든 해 2가지를 찾을때까지 반복

		while (m != 0 && i != (n + 1)) { //유망한 자식의 개수가 0이 아닐때까지 반복
			mprod = mprod * m;
			numnodes = numnodes + mprod * t;
			m = 0;
			if (promising(i, weight, total)) {
				if (weight == W) { //답
					numans = 1;
				}

				else { //답이 아닌 경우
					count_m1 = promising(i + 1, weight + w[i + 1], total - w[i + 1]); //노드의 자식 유망성 검사
					count_m2 = promising(i + 1, weight, total - w[i + 1]); //노드의 자식 유망성 검사
					m = count_m1 + count_m2; // m = v의 유망한 자식의 수

					if (m == 2) { //유망한 자식노드 무작위 선택
						i++;
						nextselect = ((rand() % 2) ? w[0] : w[i]); //0과 w[i]중에 랜덤하게 선택
						weight += nextselect;
						total -= w[i];
					}

					else if (m == 1) { //유망한 자식노드 1개인 경우 유망한 노드 선택
						i++;

						if (count_m1 == 1) {
							weight += w[i];
							total -= w[i];
						}

						else { //count_m2==1인 경우
							total -= w[i];
						}
					}
				}
			}
		}
		printf("numnodes->%u weight->%d\n", numnodes, weight);
		totalnumnodes += numnodes; //numnodes의 합

		if (numans == 1 && numnodes != ans_node) { //W=52이며 이전과 다른 조합인 경우
			numanswer++; //찾은 답의 개수 증가
			numans = 0;
			ans_node += numnodes; //찾은 조합 저장
		}

		//초기화
		i = 0;
		mprod = 1;
		numnodes = 1;
		m = 1;
		weight = 0;
		total = 106;
	}

	return totalnumnodes; //numnodes의 합 리턴
	// (노드의 총 개수 추정치들의 합 리턴)
}