class student
{
private:
    friend class database;  //设置友元类为datadase类
    string studentID;  //学生ID
    string name;  //学生姓名
    string gender;  //学生性别
    int age;  //学生年龄
    string choice;  //学生报考类别选择
    student *next;  //链表尾，指向下一个student类链表的头
};
class database
{
private:
    student *first;  //用来存放所有考生的链表头
    int studentNUM;  //用来存放所有学生的数量

    bool isEmpty();  //判断当前链表是否为空
    void SmpDisplay(student *student);	//在屏幕上打印一个学生的信息
    void HeadDisplay();  //打印信息所需要的文字头
	void search(string& id,student *&ans,student *&previous);  //依据学生ID来寻找一个考生的信息
public:
    database() :first(0), studentNUM(0) {}  //初始化数据库
    void BulidDatabase();  //构建数据库
    void AllDisplay();  //打印所有的考生信息
    void InsertStu();  //插入一个考生的信息
    void DeleteStu();  //删除一个考生的信息
    void FindStu();  //查找一个考生的信息
    void ReviseInfo();  //修改一个考生的信息
    void StatDatabase();  //统计数据库信息
};
