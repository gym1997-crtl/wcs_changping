/***************************************************************************
 **
 **  Copyright (C) 2018 MaMinJie <canpool@163.com>
 **  Contact: https://github.com/canpool
 **
 **  This program is free software: you can redistribute it and/or modify
 **  it under the terms of the GNU General Public License as published by
 **  the Free Software Foundation, either version 3 of the License, or
 **  (at your option) any later version.
 **
 **  This program is distributed in the hope that it will be useful,
 **  but WITHOUT ANY WARRANTY; without even the implied warranty of
 **  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 **  GNU General Public License for more details.
 **
 **  You should have received a copy of the GNU General Public License
 **  along with this program.  If not, see http://www.gnu.org/licenses/.
 **
****************************************************************************/
#include "skindialog.h"
#include "skinitem.h"

#define SKIN_NUM           15
#define SKIN_RES_NAME(n)   QString(":/skin/%1").arg(n)

SkinDialog::SkinDialog(QWidget *parent)
    : QDialog(parent)
{
    m_pTabWidget = 0;
    m_pLastSkinItem = 0;
    m_skinItemList.clear();
    m_pThemeComboBox = 0;
    m_themeMap.clear();

    createWindow();

    setFixedSize(800, 600); //
    setWindowTitle(tr("Change Skin Center"));
    setWindowIcon(QIcon(":/main/logo"));
}

void SkinDialog::createWindow()
{
    QWidget *pCentralWidget = new QWidget();

    QWidget *allPageWidget = new QWidget();
    QGridLayout *pGridLayout = new QGridLayout();
    pGridLayout->setSpacing(15);
    pGridLayout->setContentsMargins(20, 10, 10, 10);
    allPageWidget->setLayout(pGridLayout);

    QString currentSkin = skinName();
    QStringList skinNameList;
    for(int i = 0; i < SKIN_NUM; i++)
    {
        skinNameList<<SKIN_RES_NAME(i);
    }
    for(int i = 0; i < SKIN_NUM; i++){
        SkinItem *item = new SkinItem();
        item->setMinimumHeight(150);
        item->setPixmapName(skinNameList.at(i));
        if(currentSkin == skinNameList.at(i)){
            m_pLastSkinItem = item;
        }
        m_skinItemList.append(item);
        connect(item, SIGNAL(clicked()), this, SLOT(slotItemClicked()));
        pGridLayout->addWidget(item, i/3, i%3);
    }


    QVBoxLayout *layout = new QVBoxLayout();
    layout->setContentsMargins(0, 0, 0, 0);
    layout->setSpacing(0);
    pCentralWidget->setLayout(layout);

    // init
    if(!m_pLastSkinItem){
        m_pLastSkinItem = m_skinItemList.at(0);
    }
    m_pLastSkinItem->select(true);
    emit changeSkin(m_pLastSkinItem->pixmapName());
}

QString SkinDialog::skinName()
{
    QSettings settings("Canpool", "qtcanpool");
    QString skinName = settings.value("skin").toString();
    return skinName;
}

void SkinDialog::slotItemClicked()
{
    SkinItem *item = qobject_cast<SkinItem *>(sender());

    if(m_pLastSkinItem == item) return;
    if(m_pLastSkinItem){
        m_pLastSkinItem->select(false);
    }
    m_pLastSkinItem = item;
    m_pLastSkinItem->select(true);

    QString skinName = item->pixmapName();

    update();
    emit changeSkin(skinName);
}

void SkinDialog::slotThemeChanged(int index)
{
//     QString fileName = m_pThemeComboBox->itemData(index).toString();
//     Theme::setTheme(fileName);
//     emit themeChanged();
}
