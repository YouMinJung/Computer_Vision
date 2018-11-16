# < Computer_Vision > Projects related to computer vision

<p>Environment : vi Editor in Unix</p>
<p>Laguage : C</p>

<br><br>

# Calculate Coin - 2017.10
<p> 여러 개의 동전을 찍은 사진으로 총 얼마가 있는지 계산하는 프로그램 <p>

#### Program Flow
1) Binarizaion을 진행
	- 배경이 흰색일 수도 있고 검은색일 수도 있다. 이를 구분하여 만일 흰색이라면 반전처리 
2) Opening -> Closing을 통해 pepper와 salt를 제거
3) Labeling을 진행
4) Labeling하여 Segmentation을 한 영상을 sobel mask로 contour를 추출
	 - Perimeter를 구함
5) Contour 추출 처리를 안 한 영상으로 Area를 구함
6) Center of Mass를 구함
	- 동전인지 아닌지를 판단
7) 동전이라면 perimeter, area, center of mass값을 출력해주고 이들을 배열에 각각 저장
8) 배열에 저장된 값들을 오름차순으로 정렬
9) 정렬된 값을 토대로 area, perimeter값의 차이를 이용하여 동전을 금액별로 구분
	- 10원짜리의 경우, 과거의 10 원짜리와 현재의 10원짜리의 크기가 다르므로 이는 sub_num변수로 구분하여 계산
  
#### PDF File : 
1) [Computer_Vision_labeling1.pdf](https://github.com/YouMinJung/Computer_Vision/files/2588055/Computer_Vision_labeling1.pdf)
2) [ComputerVision_labeling1_report.pdf](https://github.com/YouMinJung/Computer_Vision/files/2588053/ComputerVision_labeling1_report.pdf)

<br><br>

# Licence and Credit Card Labeling - 2017.12
<p> 자동차 번호판과 신용카드 형식의 이미지를 내용 텍스트로 반환시켜주는 프로그램 </p>

- Machine Vision 방식이 아닌 Labeling 방식을 이용
- Template을 구성하는 일련의 과정과 Preprocessing 과정 포함
- Labeling 이외의 Image Preprocessing 과정 포함 (Rotation, Remove backgroung)

#### PDF File :
1) [ComputerVision_labeling2_report.pdf](https://github.com/YouMinJung/Computer_Vision/files/2588054/ComputerVision_labeling2_report.pdf)
2) [Computer_Vision_Labeling2.pdf](https://github.com/YouMinJung/Computer_Vision/files/2588056/Computer_Vision_Labeling2.pdf)
