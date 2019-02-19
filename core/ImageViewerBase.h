#ifndef IMAGE_VIEWER_BASE_H
#define IMAGE_VIEWER_BASE_H

#include <QWidget>
#include <QSlider>

#include <vector>

#include "DataManager.h"
#include "DataViewBase.h"

class ImageViewerBase : public QWidget
{
	Q_OBJECT

public:
	ImageViewerBase(QWidget *parent = nullptr);

	void SetDataView(DataViewBase* dataView);
	void SetDataManager(DataManager* dataManager);
	long AddSlider(QSlider* slider); // Can be used multiple times

public slots:
	// Slot for slider
	virtual void SliderHandler(long sliderNumber, int value);

	// Slots for DataViewBase
	virtual void SelectedSubjectChangedHandler(long uid);
	virtual void SelectedDataChangedHandler(long iid);
	virtual void DataCheckedStateChangedHandler(long iid, bool checkState); //optional

	// Slot, but probably just called.
	virtual void SaveImageToFile(long iid);

protected:
	// Override this to connect custom signal 
	// (triggered from slider's valueChanged) signal 
	// to slot SliderHandler
	virtual void ConnectSlider(QSlider* slider) {}

	DataManager* m_DataManager;
	long m_SlidersCount;
};

#endif // ! IMAGE_VIEWER_BASE_H