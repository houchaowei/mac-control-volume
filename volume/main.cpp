#include <iostream>
#include <CoreAudio/CoreAudio.h>
#include <AudioToolbox/AudioToolbox.h>

using namespace std;

static int getVolume() {
	AudioDeviceID defaultOutputDevice;
	UInt32 propertySize = sizeof(defaultOutputDevice);

	AudioObjectPropertyAddress propertyAddress = {
		kAudioHardwarePropertyDefaultOutputDevice,
		kAudioObjectPropertyScopeGlobal,
		kAudioObjectPropertyElementMaster
	};

	OSStatus status = AudioObjectGetPropertyData(kAudioObjectSystemObject, &propertyAddress, 0, nullptr, &propertySize, &defaultOutputDevice);

	if (status != noErr) {
		cout << "AudioObjectGetPropertyData error (default output device): " << status << " (hex: " << hex << status << dec << ")" << endl;
		return -1;
	}

	Float32 volume = 0;
	propertyAddress.mSelector = kAudioHardwareServiceDeviceProperty_VirtualMainVolume;
	propertyAddress.mScope = kAudioDevicePropertyScopeOutput;
	propertyAddress.mElement = kAudioObjectPropertyElementMaster;

	propertySize = sizeof(volume);
	status = AudioObjectGetPropertyData(defaultOutputDevice, &propertyAddress, 0, nullptr, &propertySize, &volume);

	if (status != noErr) {
		cout << "AudioObjectGetPropertyData error (virtual main volume): " << status << " (hex: " << hex << status << dec << ")" << endl;
		return -1;
	}

	return static_cast<int>(volume * 100);
}

static int getMicVolume() {
  AudioDeviceID defaultOutputDevice;
  UInt32 propertySize = sizeof(defaultOutputDevice);

  AudioObjectPropertyAddress propertyAddress = {
	kAudioHardwarePropertyDefaultInputDevice,
	kAudioObjectPropertyScopeGlobal,
	kAudioObjectPropertyElementMaster
  };

  OSStatus status = AudioObjectGetPropertyData(kAudioObjectSystemObject, &propertyAddress, 0, nullptr, &propertySize, &defaultOutputDevice);

  if (status != noErr) {
	cout << "AudioObjectGetPropertyData error (default output device): " << status << " (hex: " << hex << status << dec << ")" << endl;
	return -1;
  }

  Float32 volume = 0;
  propertyAddress.mSelector = kAudioHardwareServiceDeviceProperty_VirtualMainVolume;
  propertyAddress.mScope = kAudioDevicePropertyScopeInput;
  propertyAddress.mElement = kAudioObjectPropertyElementMaster;

  propertySize = sizeof(volume);
  status = AudioObjectGetPropertyData(defaultOutputDevice, &propertyAddress, 0, nullptr, &propertySize, &volume);

  if (status != noErr) {
	cout << "AudioObjectGetPropertyData error (virtual main volume): " << status << " (hex: " << hex << status << dec << ")" << endl;
	return -1;
  }
  // 输出整型音量值
  return static_cast<int>(volume * 100);
}

// 设置扬声器音量
static void setVolume(float volume) {
  AudioDeviceID defaultOutputDevice;
  UInt32 propertySize = sizeof(defaultOutputDevice);

  AudioObjectPropertyAddress propertyAddress = {
	kAudioHardwarePropertyDefaultOutputDevice,
	kAudioObjectPropertyScopeGlobal,
	kAudioObjectPropertyElementMaster
  };

  OSStatus status = AudioObjectGetPropertyData(kAudioObjectSystemObject, &propertyAddress, 0, nullptr, &propertySize, &defaultOutputDevice);

  if (status != noErr) {
	cout << "AudioObjectGetPropertyData error (default output device): " << status << " (hex: " << hex << status << dec << ")" << endl;
	return;
  }

  propertyAddress.mSelector = kAudioHardwareServiceDeviceProperty_VirtualMainVolume;
  propertyAddress.mScope = kAudioDevicePropertyScopeOutput;
  propertyAddress.mElement = kAudioObjectPropertyElementMaster;

  propertySize = sizeof(volume);
  status = AudioObjectSetPropertyData(defaultOutputDevice, &propertyAddress, 0, nullptr, propertySize, &volume);

  if (status != noErr) {
	cout << "AudioObjectSetPropertyData error (virtual main volume): " << status << " (hex: " << hex << status << dec << ")" << endl;
	return;
  }
}

// 设置麦克风音量
static void setMicVolume(float volume) {
  AudioDeviceID defaultOutputDevice;
  UInt32 propertySize = sizeof(defaultOutputDevice);

  AudioObjectPropertyAddress propertyAddress = {
	kAudioHardwarePropertyDefaultInputDevice,
	kAudioObjectPropertyScopeGlobal,
	kAudioObjectPropertyElementMaster
  };

  OSStatus status = AudioObjectGetPropertyData(kAudioObjectSystemObject, &propertyAddress, 0, nullptr, &propertySize, &defaultOutputDevice);

  if (status != noErr) {
	cout << "AudioObjectGetPropertyData error (default output device): " << status << " (hex: " << hex << status << dec << ")" << endl;
	return;
  }

  propertyAddress.mSelector = kAudioHardwareServiceDeviceProperty_VirtualMainVolume;
  propertyAddress.mScope = kAudioDevicePropertyScopeInput;
  propertyAddress.mElement = kAudioObjectPropertyElementMaster;

  propertySize = sizeof(volume);
  status = AudioObjectSetPropertyData(defaultOutputDevice, &propertyAddress, 0, nullptr, propertySize, &volume);

  if (status != noErr) {
	cout << "AudioObjectSetPropertyData error (virtual main volume): " << status << " (hex: " << hex << status << dec << ")" << endl;
	return;
  }
}

// 输出是否静音
static bool isMute() {
  AudioDeviceID defaultOutputDevice;
  UInt32 propertySize = sizeof(defaultOutputDevice);

  AudioObjectPropertyAddress propertyAddress = {
	kAudioHardwarePropertyDefaultOutputDevice,
	kAudioObjectPropertyScopeGlobal,
	kAudioObjectPropertyElementMaster
  };

  OSStatus status = AudioObjectGetPropertyData(kAudioObjectSystemObject, &propertyAddress, 0, nullptr, &propertySize, &defaultOutputDevice);

  if (status != noErr) {
	cout << "AudioObjectGetPropertyData error (default output device): " << status << " (hex: " << hex << status << dec << ")" << endl;
	return false;
  }

  UInt32 mute = 0;
  propertyAddress.mSelector = kAudioDevicePropertyMute;
  propertyAddress.mScope = kAudioDevicePropertyScopeOutput;
  propertyAddress.mElement = kAudioObjectPropertyElementMaster;

  propertySize = sizeof(mute);
  status = AudioObjectGetPropertyData(defaultOutputDevice, &propertyAddress, 0, nullptr, &propertySize, &mute);

  if (status != noErr) {
	cout << "AudioObjectGetPropertyData error (mute): " << status << " (hex: " << hex << status << dec << ")" << endl;
	return false;
  }

  return mute == 1;
}

// 设置静音
static void setMute(bool mute) {
  AudioDeviceID defaultOutputDevice;
  UInt32 propertySize = sizeof(defaultOutputDevice);

  AudioObjectPropertyAddress propertyAddress = {
	kAudioHardwarePropertyDefaultOutputDevice,
	kAudioObjectPropertyScopeGlobal,
	kAudioObjectPropertyElementMaster
  };

  OSStatus status = AudioObjectGetPropertyData(kAudioObjectSystemObject, &propertyAddress, 0, nullptr, &propertySize, &defaultOutputDevice);

  if (status != noErr) {
	cout << "AudioObjectGetPropertyData error (default output device): " << status << " (hex: " << hex << status << dec << ")" << endl;
	return;
  }

  UInt32 muteValue = mute ? 1 : 0;
  propertyAddress.mSelector = kAudioDevicePropertyMute;
  propertyAddress.mScope = kAudioDevicePropertyScopeOutput;
  propertyAddress.mElement = kAudioObjectPropertyElementMaster;

  propertySize = sizeof(muteValue);
  status = AudioObjectSetPropertyData(defaultOutputDevice, &propertyAddress, 0, nullptr, propertySize, &muteValue);

  if (status != noErr) {
	cout << "AudioObjectSetPropertyData error (mute): " << status << " (hex: " << hex << status << dec << ")" << endl;
	return;
  }
}

// 监听音量变化
static OSStatus volumeChanged(AudioObjectID inObjectID, UInt32 inNumberAddresses, const AudioObjectPropertyAddress inAddresses[], void *inClientData) {
  for (int i = 0; i < inNumberAddresses; i++) {
	if (inAddresses[i].mSelector == kAudioHardwareServiceDeviceProperty_VirtualMainVolume) {
	  Float32 volume = 0;
	  UInt32 dataSize = sizeof(volume);
	  OSStatus status = AudioObjectGetPropertyData(inObjectID, &inAddresses[i], 0, nullptr, &dataSize, &volume);

	  if (status != noErr) {
		cout << "AudioObjectGetPropertyData error (virtual main volume): " << status << " (hex: " << hex << status << dec << ")" << endl;
		return status;
	  }

	  cout << static_cast<int>(volume * 100) << endl;
	}
  }

  return noErr;
}

// 监听系统输出音量变化，当音量变化时，输出音量
static void listenVolumeChange() {
  AudioDeviceID defaultOutputDevice;
  UInt32 propertySize = sizeof(defaultOutputDevice);

  AudioObjectPropertyAddress propertyAddress = {
	kAudioHardwarePropertyDefaultOutputDevice,
	kAudioObjectPropertyScopeGlobal,
	kAudioObjectPropertyElementMaster
  };

  OSStatus status = AudioObjectGetPropertyData(kAudioObjectSystemObject, &propertyAddress, 0, nullptr, &propertySize, &defaultOutputDevice);

  if (status != noErr) {
	cout << "AudioObjectGetPropertyData error (default output device): " << status << " (hex: " << hex << status << dec << ")" << endl;
	return;
  }

  propertyAddress.mSelector = kAudioHardwareServiceDeviceProperty_VirtualMainVolume;
  propertyAddress.mScope = kAudioDevicePropertyScopeOutput;
  propertyAddress.mElement = kAudioObjectPropertyElementMaster;

  Float32 volume = 0;
  propertySize = sizeof(volume);
  status = AudioObjectAddPropertyListener(defaultOutputDevice, &propertyAddress, volumeChanged, nullptr);

  if (status != noErr) {
	cout << "AudioObjectAddPropertyListener error (virtual main volume): " << status << " (hex: " << hex << status << dec << ")" << endl;
	return;
  }
}

// 监听输入音量变化，当音量变化时，输出音量
static void listenMicVolumeChange() {
  AudioDeviceID defaultOutputDevice;
  UInt32 propertySize = sizeof(defaultOutputDevice);

  AudioObjectPropertyAddress propertyAddress = {
	kAudioHardwarePropertyDefaultInputDevice,
	kAudioObjectPropertyScopeGlobal,
	kAudioObjectPropertyElementMaster
  };

  OSStatus status = AudioObjectGetPropertyData(kAudioObjectSystemObject, &propertyAddress, 0, nullptr, &propertySize, &defaultOutputDevice);

  if (status != noErr) {
	cout << "AudioObjectGetPropertyData error (default output device): " << status << " (hex: " << hex << status << dec << ")" << endl;
	return;
  }

  propertyAddress.mSelector = kAudioHardwareServiceDeviceProperty_VirtualMainVolume;
  propertyAddress.mScope = kAudioDevicePropertyScopeInput;
  propertyAddress.mElement = kAudioObjectPropertyElementMaster;

  Float32 volume = 0;
  propertySize = sizeof(volume);
  status = AudioObjectAddPropertyListener(defaultOutputDevice, &propertyAddress, volumeChanged, nullptr);

  if (status != noErr) {
	cout << "AudioObjectAddPropertyListener error (virtual main volume): " << status << " (hex: " << hex << status << dec << ")" << endl;
	return;
  }
}


int main(int argc, char *argv[]) {
  // 当输入的参数为-o时，只输出一次扬声器音量
  if (argc == 2 && strcmp(argv[1], "-o") == 0) {
	int volume = getVolume();
	cout << volume << endl;
	return 0;
  }
  // 当输入的参数为 -mo 时，输出麦克风音量
  else if (argc == 2 && strcmp(argv[1], "-mo") == 0) {
   int volume = getMicVolume();
   cout << volume << endl;
   return 0;
  }
  // 当输入的参数为 -s 时，设置音量
  else if (argc == 3 && strcmp(argv[1], "-s") == 0) {
   float volume = atof(argv[2]);
   volume = volume / 100;
   setVolume(volume);
   return 0;
 }
  // 当输入参数为 -ms 时，设置麦克风音量
  else if (argc == 3 && strcmp(argv[1], "-ms") == 0) {
	float volume = atof(argv[2]);
	volume = volume / 100;
	setMicVolume(volume);
	return 0;
  }
  // 当输入的参数为 -mute 时，输出是否静音
  else if (argc == 2 && strcmp(argv[1], "-mute") == 0) {
	bool mute = isMute();
	cout << boolalpha << mute << endl;
	return 0;
  }
  // 当输入的参数为 -mute true 时，设置是否静音
  else if (argc == 3 && strcmp(argv[1], "-mute") == 0) {
	bool mute = strcmp(argv[2], "true") == 0;
	setMute(mute);
	return 0;
  }
  // 监听系统输出音量变化, 当音量变化时，触发 OnNotify 方法
  else if (argc == 2 && strcmp(argv[1], "-w") == 0) {
	listenVolumeChange();
	while (true) {
	  sleep(1);
	}
  }
  // 监听麦克风音量变化, 当音量变化时，触发 OnNotify 方法
  else if (argc == 2 && strcmp(argv[1], "-wm") == 0) {
	listenMicVolumeChange();
	while (true) {
	  sleep(1);
	}
  }
  else {
	cout << "Usage: volume [-o] [-s] [-l] [-mute] [-h]" << endl;
	cout << "Options:" << endl;
	cout << "  -o: get volume" << endl;
	cout << "  -s: set volume" << endl;
	cout << "  -l: listen volume change" << endl;
	cout << "  -mute: get mute" << endl;
	cout << "  -h: help" << endl;
	return 0;
  }
}

