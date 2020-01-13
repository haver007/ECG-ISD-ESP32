#pragma once
#include <SD.h>

enum class StorageError {
	None,
	CannotInitialize,
	FileSystemError, 
	TooManyFiles,
	CanNotOpenFile
};

enum class StorageState { Idle, Error, Recording };

class Storage {
	int lastFileIndex = 0;
	File currentFile;
	StorageState state_ = StorageState::Idle;
	StorageError error_ = StorageError::None;

	bool init();
	void setError(StorageError error);
	

public:
	Storage();
	bool beginRecording();
	bool endRecording();
    bool writeRecord(const float data[], uint8_t length);
    int readRecord(float data[], uint8_t length);
	void loop();
	StorageError getError() const;
	bool clearError();
	StorageState isRecording(); 
};
