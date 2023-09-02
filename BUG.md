1.登录界面更改

2.帮助文档展示

3.指标点设置和课程目标

4.选择框设置



1.二级导航栏加粗

2.二级导航自动展开

3.培养方案查看与教学大纲形式一致

4.教学大纲列出所有课程,有的打勾...... 不展示删除按钮,加上下载按钮,上传按钮和课程对应

5.课程基本信息: 先选专业,类别,课程名称  班级以选择的形式构成

6.课程基本信息界面 操作按钮简化

7.试卷设置 小题课程目标和指标点列表的顺序问题

8.学生成绩管理模块 添加学生信息管理在成绩管理之前





1.教学大纲上传按照老师给权限

2.在课程基本信息设置中可以查看教学大纲



1.添加调查问卷在学生管理模块成绩管理同级



1.zqh 计算机组成原理

2.ljq c语言



#### 数据库相关改动

```sql
alter table course_target_analyse add CONSTRAINT 课程目标分析表链接课程基本信息表 FOREIGN KEY (course_id) REFERENCES course_basic_information(id) ON DELETE CASCADE ON UPDATE CASCADE;
```

```sql
alter table course_target_analyse add target_id int(11) DEFAULT 1 AFTER course_id;
```

```sql
alter table course_target_analyse add CONSTRAINT 课程目标分析表链接课程目标表 FOREIGN KEY (target_id) REFERENCES course_target(id) ON DELETE CASCADE ON UPDATE CASCADE;
```



```

```

