#ifndef DATA_TREE_VIEW_H
#define DATA_TREE_VIEW_H

#include <QWidget>
#include <QTreeWidget>
#include <QTreeWidgetItem>
#include <QProgressBar>

#include <map>

#include "DataViewBase.h"

class DataTreeView : public DataViewBase
{
	Q_OBJECT

public:
	// For storing information about the tree's items
	const int ID         = Qt::UserRole;
	const int IS_CHECKED = Qt::UserRole + 1;

	DataTreeView(QWidget *parent = nullptr);

	bool IsDataChecked(long iid) override;
	void SetDataCheckedState(long iid, bool checkState, bool imitateClick = false) override;

public slots:
	// Slots overriden from DataViewBase
	void SubjectAddedHandler(long uid) override;
	void SubjectRemovedHandler(long uid) override;
	void SubjectDataChangedHandler(long uid) override;
	void UpdateProgressHandler(long uid, QString message, int progress) override;

	// Internal slots
	void OnItemClick(QTreeWidgetItem *item, int column);
	void OnItemRightClick(const QPoint& pos);
	void OnItemRightClickRemove();
	void OnItemRightClickSetAsSeeds();
	void OnItemRightClickSetAsSegmentation();
	void OnItemRightClickExport();

private:
	/** For convenience a function to change to a new subject */
	void SwitchExpandedView(QTreeWidgetItem* focusItem);

	QTreeWidget* m_TreeWidget;
	std::map<long, QTreeWidgetItem*> m_Subjects;
	std::map<long, QTreeWidgetItem*> m_Data;
	std::map<long, QProgressBar*>    m_SubjectProgressBars;
};

#endif // ! DATA_TREE_VIEW_H
