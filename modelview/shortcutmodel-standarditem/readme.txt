Action Editor library.
This is an example of why one should NOT use the QStandardItemModel
and instead extend from an abstract table model.
The problem is: when you modify the shortcut, you can't see the updated
info in the table without some sort of event notification.
We do not want to store duplicate copies of the data in our standard items.
Therefore, the better approach is to extend from AbstractTableModel,
as shown in the "shortcutmodel" example.
