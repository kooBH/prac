# 발화 추출기   
2022-02-17
  
그랜드챌린지 데이터 가공을 위한 코드    

임의의 포맷(wav,mp3,m4a | 16kHz, 48kHz, 44.1kHz | 1ch, 2ch)의 오디오 파일을 읽어서  

발화별로 잘라서 16kHz 단일채널 오디오를 추출하여 저장  

+ 사용  

```
python extractor.py -i <입력폴더> -o <출력폴더>
```
