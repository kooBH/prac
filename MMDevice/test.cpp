
#include "common.h"

struct BufferController {
  BYTE* bpBackupBuffer;
  unsigned long ulPushBytes;
  unsigned long ulPopBytes;
  unsigned long ulBufferSize;
};

bool isMicFrameOver = 0;
bool isRecordFinish = 0;
bool isSpeakerFrameOver = 0;
bool isCaptureFinish = 0;
bool bIsFirstFrame = 1;
unsigned long ulSpeakerTotalFrame = 0;
unsigned long ulSpeakerFrameCounter = 0;
unsigned long ulSpeakerSavedIndex = 0, ulSpeakerProcessedIndex = 0;
BufferController FarendBuffer, InputBuffer;

int main(int argc, char *argv[]) {


  HRESULT hr = S_OK;
  unsigned int channels, fs, bufferFrames, device = 0, offset = 0;
  double time = 2.0;
  FILE* fd;

  hr = CoInitialize(NULL);
  if (FAILED(hr)) {
    ERR(L"CoInitialize failed: hr = 0x%08x", hr);
    return -__LINE__;
  }
  CoUninitializeOnExit cuoe;

  // parse command line
  //CPrefs prefs(argc, argv, hr);
  CPrefs prefs(argc, NULL, hr);
  if (FAILED(hr)) {
    ERR(L"CPrefs::CPrefs constructor failed: hr = 0x%08x", hr);
    return -__LINE__;
  }
  if (S_FALSE == hr) {
    // nothing to do
    return 0;
  }

  // create a "loopback capture has started" event
  HANDLE hStartedEvent = CreateEvent(NULL, FALSE, FALSE, NULL);
  if (NULL == hStartedEvent) {
    ERR(L"CreateEvent failed: last error is %u", GetLastError());
    return -__LINE__;
  }
  CloseHandleOnExit closeStartedEvent(hStartedEvent);

  // create a "stop capturing now" event
  HANDLE hStopEvent = CreateEvent(NULL, FALSE, FALSE, NULL);
  if (NULL == hStopEvent) {
    ERR(L"CreateEvent failed: last error is %u", GetLastError());
    return -__LINE__;
  }
  CloseHandleOnExit closeStopEvent(hStopEvent);

  // create arguments for loopback capture thread
  LoopbackCaptureThreadFunctionArguments threadArgs;
  threadArgs.hr = E_UNEXPECTED; // thread will overwrite this
  threadArgs.pMMDevice = prefs.m_pMMDevice;
  threadArgs.bInt16 = 1;// prefs.m_bInt16;
  threadArgs.hFile = prefs.m_hFile;
  threadArgs.hStartedEvent = hStartedEvent;
  threadArgs.hStopEvent = hStopEvent;
  threadArgs.nFrames = 0;
  return 0;
}