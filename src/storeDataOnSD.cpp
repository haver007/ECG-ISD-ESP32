#include "storeDataOnSD.h"
#include <SPI.h>

bool Storage::init() {
	if (!SD.begin()) {
        Serial.printf("Storage::init begin error");
		setError(StorageError::CannotInitialize);
		return false;
	}

	if (!SD.exists("/recordings")) {
		if (!SD.mkdir("/recordings")) {
	        Serial.printf("Storage::init mkdir /recordings error");
			setError(StorageError::FileSystemError);
			return false;
		}
	}

	state_ = StorageState::Idle;

	return true;
};

Storage::Storage(){};

void Storage::setError(StorageError error) {
	state_ = StorageState::Error;
	error_ = error;
};

bool Storage::writeRecord(const float data[], uint8_t length) {

	if (state_ != StorageState::Idle) {
		return 0;
	}

	if (!currentFile.write(length)) {
		setError(StorageError::FileSystemError);
		return false;
	}

	if (!currentFile.write((const uint8_t*)data, sizeof(float) * length)) {
		setError(StorageError::FileSystemError);
		return false;
	}

	return true;
};

int Storage::readRecord(float data[], uint8_t length) {

	if (state_ != StorageState::Idle) {
		return 0;
	}

	int dataLength;

	if ((dataLength = currentFile.peek()) == -1) {
		setError(StorageError::FileSystemError);
		return 0;
	}

	if (dataLength >= length) {
		return -dataLength;
	}

	if ((dataLength = currentFile.read()) == -1) {
		setError(StorageError::FileSystemError);
		return 0;
	}

	if (!currentFile.read((uint8_t*)data, sizeof(float) * length)) {
		setError(StorageError::FileSystemError);
		return 0;
	}

	return dataLength;
};

StorageState isRecording() {
	return StorageState::Recording;
};

StorageError Storage::getError() const {
	return error_;
};

bool Storage::clearError() {
	if (!init()) {
		Serial.println("Clear error failed");
		return false;
	}
	state_ = StorageState::Idle;
	error_ = StorageError::None;

	return true;
};

bool Storage::beginRecording() {
	if (state_ == StorageState::Error) {
		return false;
	}

	char fileName[23];
	bool fileFound = false;
	for (int i = lastFileIndex; i < 10000; i++) {

		snprintf(fileName, 23, "/recordings/%05d.rec", i);
		if (!SD.exists(fileName)) {
			fileFound = true;
			break;
		}
	}
	if (!fileFound) {
		setError(StorageError::TooManyFiles);
		return false;
	}
	currentFile = SD.open(fileName, FILE_WRITE);
	if (!currentFile.available()) {
		setError(StorageError::CanNotOpenFile);
		return false;
	}
	state_ = StorageState::Recording;

	return true;
};

bool Storage::endRecording() {
	if (currentFile.available()) {
		currentFile.close();
	}
	state_ = StorageState::Idle;
	lastFileIndex++;

	return true;
};

void Storage::loop() {
	Serial.println("Welcome");

	if (!init()) {
		Serial.println("First init failed");
	}

	while (true) {
		switch (state_) {
		case StorageState::Idle:
			break;
		case StorageState::Error:
			break;
		case StorageState::Recording:
			break;
		}
		delay(1);
	}
};
