#ifndef MAINWINDOW_H
#define MAINWINDOW_H


#include <QtWidgets/QMainWindow>
#include <QMimeData>
#include <QDragEnterEvent>
#include <QTreeWidget>
#include <QTreeWidgetItem>
#include <QProgressBar>
#include <QHBoxLayout>
#include <QGraphicsDropShadowEffect>
#include <QDir>
#include <QFileDialog>
#include <QMessageBox>
#include <QTextStream>
#include <QDebug>
#include <QLabel>

#include <mutex>
#include <vector>

#include "ui_MainWindow.h"
#include "Scheduler.h"
#include "ViewerBase.h"

#ifdef BUILD_VIEWER
#include "MpipMitkViewer.h"
//#include "VtkViewer.h"
#endif

namespace Ui {
  class MainWindow;
}

class MainWindow : public QMainWindow
{
  Q_OBJECT

public:
  const int IMAGE_PATH_ROLE  = Qt::UserRole;
  const int IMAGE_NAME_ROLE  = Qt::UserRole + 1;
  const int PATIENT_UID_ROLE = Qt::UserRole + 2;
  const int MPIP_ROLE        = Qt::UserRole + 3;

  explicit MainWindow(QWidget *parent = nullptr);
  ~MainWindow();

  void dragEnterEvent(QDragEnterEvent *e) override;

  void dropEvent(QDropEvent *e) override;

public slots:
  void OnOpenSingleSubject();
  void handleConfigButton();
  void OnTreeWidgetClicked(QTreeWidgetItem *item, int column);
  void ShowTreeContextMenu(const QPoint& pos);
  void TreeContextRemoveItem();
  void TreeContextSetItemAsMask();
  void RunPressed();
  void SchedulerResultReady(long uid);
  void UpdateProgress(long uid, int progress); // Updates progress for a single subject

protected:
  void Load(QString filePath, QString overlayPath = QString());

private:
  /** Loads all the images of a single patient */
  bool LoadSingleSubject(QString directoryPath);

  /** Loads all the images from a directory, and calls itself for subdirectories */
  void LoadAllFilesRecursive(QString directoryPath, QStringList& allFiles);

  void SwitchSubjectAndImage(long uid, QString imagePath);

  Ui::MainWindow *ui;

  std::mutex m_TreeEditMutex; // Used so that no parallel additions/deletions happen simultaneously

  QStringList m_AcceptedFileTypes = QStringList() << "*.nii.gz" << "*.dcm" << "*.dicom" << "*.nrrd";
  long uidNextToGive = 0;
  std::map<long, QTreeWidgetItem*> subjectByUid;
  Scheduler m_Scheduler;

  //VtkViewer* m_VtkViewer;
  ViewerBase* m_Viewer;
};

#endif // MAINWINDOW_H