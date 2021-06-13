#ifndef SQLCONF_H
#define SQLCONF_H

#include <QSqlDatabase>
#include <QSqlQuery>
#include <QMessageBox>
#include <QSqlError>

#define property_primary_key "PRIMARY KEY" //主键
#define property_not_null "NOT NULL" //非空
#define property_unique "UNIQUE" //唯一
#define property_foregin "FOREIGN KEY" //外键
#define property_auto_increment "AUTO_INCREMENT" //具有自增长属性

#define create_databases(dbname)\
    QSqlDatabase dbname = QSqlDatabase::addDatabase("QODBC");\
    dbname.setHostName("127.0.0.1");\
    dbname.setPort(3306);\
    dbname.setDatabaseName("01");\
    dbname.setUserName("root");\
    dbname.setPassword("123456")
#define open_database(dbname)\
    bool ok = dbname.open();\
    if (ok){\
        QMessageBox::information(this, "infor", "success");\
    }\
    else {\
        QMessageBox::information(this, "infor",\
        QString("open failed reason:%1").arg(db.lastError().text()));\
    }
//创建表
#define create_table(tablename,colnamesanproper)\
    QString("create table %1(%2);").arg(tablename).arg(colnamesanproper)
//插入数据
#define insert_many_valuesinto_table(tablename,values)\
    QString("insert into %1 values %2;").arg(tablename).arg(values)
#define insertinto_table(tablename,values)\
    QString("insert into %1 values (%2);").arg(tablename).arg(values)
#define insert_valuesinto_table(tablename,clonames,values)\
    QString("insert into %1(%2) values(%3)").arg(tablename).arg(clonames).arg(values)
//查找数据 DISTINCT 不重复（where后可使用int notin betweenand like ORDER BY [ASC|DESC] ）
#define select_table_where(tablename,showcolnames,where)\
    QString("select %1 from %2 where %3;").arg(showcolnames).arg(tablename).arg(where)
#define select_table(tablename,showcolnames)\
    QString("select %1 from %2;").arg(showcolnames).arg(tablename)
#define select_table_useFULLTEXT(tablename,colname,keywords,showcolnames)\
    QString("SELECT %1 FROM %2 WHERE MATCH(%3) AGAINST(%4);").arg(showcolnames).arg(tablename).arg(colname).arg(keywords)
//更新数据
#define update_datas(tablename,colname,olddata,newdata)\
    QString("update %1 set %2 = %3 where colname = %4;")\
    .arg(tablename).arg(colname).arg(olddata).arg(newdata) //  #通过id 字段匹配更新记录
#define update_datas_where(tablename,oldwhere,newwhere)\
    QString("update %1 set %2 where %3;").arg(tablename).arg(oldwhere).arg(newwhere)
//删除数据
#define delete_datas(tablename,where)\
   QString("delete from %1 where %2;").arg(tablename).arg(where)
#define delete_all_datas(tablename)\
   QString("delete from %1;").arg(tablename)
//调整列的完整性约束
#define add_constraints(tablename,colname,constraints)\
    QString("alter table %1 modify %2 %3;").arg(tablename).arg(colname).arg(constraints)   // #设置默认值和非空
#define delete_constraints(tablename,colname)\
    QString("alter table %1 modify %2;").arg(tablename).arg(colname)   //#取消默认值和非空
//追加索引
#define add_INDEX_ASC(indexname,tablename,colname)\
    QString("create index %1 on %2(%3 ASC);").arg(indexname).arg(tablename).arg(colname)// #追加升序索引
#define add_INDEX_DESC(indexname,tablename,colname)\
    QString("create index %1 on %2(%3 DESC);").arg(indexname).arg(tablename).arg(colname)// #追加降序索引
#define add_FULLTEXT_INDEX(indexname,tablename,colname)\
    QString("create FULLTEXT index %1 on %2(%3);").arg(indexname).arg(tablename).arg(colname)// #追加全文索引
#define set_INDEX_INVISIBLE(indexname,tablename)\
    QString("ALTER TABLE %1 ALTER  INDEX  %2 INVISIBLE;").arg(tablename).arg(indexname) //#隐藏索引
#define set_INDEX_VISIBLE(indexname,tablename)\
    QString("ALTER TABLE %1 ALTER  INDEX  %2 INVISIBLE;").arg(tablename).arg(indexname)// #取消隐藏
#define delete_INDEX(indexname,tablename)\
    QString("DROP INDEX %1 ON %2;").arg(indexname).arg(tablename)//  删除索引

#endif // SQLCONF_H
