import whisper
import librosa as rs
import time

path = "../data/speech_male_kor.wav"

x,_ = rs.load(path,16000)


# load audio and pad/trim it to fit 30 seconds
audio = whisper.load_audio(path)
audio = whisper.pad_or_trim(audio)

# make log-Mel spectrogram and move to the same device as the model
mel = whisper.log_mel_spectrogram(audio).to("cuda:0")

for size in ["tiny","base","small","medium","large"] : 

    model = whisper.load_model(size)

    # detect the spoken language
    _, probs = model.detect_language(mel)
    #print(f"Detected language: {max(probs, key=probs.get)}")

    # decode the audio
    tic = time.time()
    options = whisper.DecodingOptions()
    result = whisper.decode(model, mel, options)

    # print the recognized text
    print(result.text)

    toc = time.time()
    print("{} | {:.3f} sec".format(size,toc-tic))