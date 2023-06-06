#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <sstream>

using namespace std;

const int MAX=200; //���ŵ���

class diskScheduling
{
private:
    static int startIndexCon;
    int startIndex; // ��ͷ��ʼλ��
    vector<int> request; // ��������
public:
    diskScheduling(int startIndex=0):startIndex(startIndex)
    {
        initRequestAndStartIndex();
    }
    void initRequestAndStartIndex(); // ��ʼ����������
    void FCFS(int ss=startIndexCon); // �����ȷ���
    void SSTF(int ss=startIndexCon); // ���Ѱ��ʱ������
    void SCAN(int ss=startIndexCon,bool opreational=true); // ɨ���㷨,opreationalΪtrue��ʾ����ɨ�裬false��ʾ����ɨ��
    void C_SCAN(int ss=startIndexCon,bool opreational = true); // ѭ��ɨ���㷨
};

int diskScheduling::startIndexCon=0;

void diskScheduling::initRequestAndStartIndex()
{
    string str;
    getline(cin,str);
    stringstream ss(str); // ���ַ���ת��Ϊ��
    int temp;
    while(ss>>temp)
    {
        request.push_back(temp);
    }
    startIndexCon=startIndex;
}

void diskScheduling::FCFS(int ss)
{
    startIndex=ss;
    int sum=0;
    cout<<"�����ȷ����㷨��"<<endl;
    cout<<"��ͷ��ʼλ�ã�"<<startIndex<<endl;
    cout<<"�ŵ��������У�";
    for(int i=0;i<request.size();i++)
    {
        cout<<request[i]<<" ";
        sum+=abs(startIndex-request[i]); // �����ƶ��ŵ���
        startIndex=request[i];
    }
    cout<<endl;
    cout<<"�ƶ��ŵ�����"<<sum<<endl;
    cout<<"ƽ��Ѱ�����ȣ�"<<(double)sum/request.size()<<endl;
}

void diskScheduling::SSTF(int ss)
{
    startIndex=ss;
    int sum=0;
    cout<<"���Ѱ��ʱ�������㷨��"<<endl;
    cout<<"��ͷ��ʼλ�ã�"<<startIndex<<endl;
    cout<<"�ŵ��������У�";
    vector<int> temp=request;
    sort(temp.begin(),temp.end()); // ��������������
    int index=0;
    while(!temp.empty())
    {
        int min=MAX;
        int minIndex=0;
        for(int i=0;i<temp.size();i++)
        {
            if(abs(startIndex-temp[i])<min) // �ҵ����Ѱ��ʱ��
            {
                min=abs(startIndex-temp[i]);
                minIndex=i; // ��¼���Ѱ��ʱ����±�
            }
        }
        cout<<temp[minIndex]<<" ";
        sum+=min;
        startIndex=temp[minIndex];
        temp.erase(temp.begin()+minIndex); // ɾ���Ѿ����ʵĴŵ�
    }
    cout<<endl;
    cout<<"�ƶ��ŵ�����"<<sum<<endl;
    cout<<"ƽ��Ѱ�����ȣ�"<<(double)sum/request.size()<<endl;
}


// ����ɨ�躯�����ڸ���SCAN��C_SCAN����
int oneWayScan(const vector<int> &temp,int startIndex,bool opreational)
{
    int sum=0;
    // tempΪ�Ѿ��������������
    if(opreational) // ����ɨ��
    {
        for(int i=0;i<temp.size();i++)
        {
            cout<<temp[i]<<" ";
            sum+=abs(startIndex-temp[i]); // �����ƶ��ŵ���
            startIndex=temp[i];
        }
    }
    else // ����ɨ��
    {
        for(int i=temp.size()-1;i>=0;i--)
        {
            cout<<temp[i]<<" ";
            sum+=abs(startIndex-temp[i]); // �����ƶ��ŵ���
            startIndex=temp[i];
        }
    }
    return sum;
}

void diskScheduling::SCAN(int ss,bool opreational)
{
    startIndex=ss;
    int sum=0;
    cout<<"ɨ���㷨��"<<endl;
    cout<<"��ͷ��ʼλ�ã�"<<startIndex<<endl;
    cout<<"�ŵ��������У�";
    vector<int> temp=request;
    sort(temp.begin(),temp.end()); // ��������������
    int index=0,i;
    if(opreational) // ����ɨ��
    {
        for(i=0;i<temp.size();i++)
        {
            if(temp[i]>=startIndex) // �ҵ���һ�����ڵ��ڴ�ͷλ�õĴŵ�
            {
                index=i;
                break;
            }
        }
        while(index<temp.size())
        {
            sum+=abs(startIndex-temp[index]); // �����ƶ��ŵ���
            cout<<temp[index]<<" ";
            startIndex=temp[index];
            index++;
        }
        temp.resize(i); // ɾ���Ѿ����ʵĴŵ�
        opreational=!opreational; // �ı�ɨ�跽��
        sum+=oneWayScan(temp,startIndex,opreational); // ��������ɨ����ƶ��ŵ���
    }
    else // ����ɨ��
    {
        int i;
        for(i=temp.size()-1;i>=0;i--)
        {
            if(temp[i]<=startIndex) // �ҵ���һ��С�ڵ��ڴ�ͷλ�õĴŵ�
            {
                index=i;
                break;
            }
        }
        while(index>=0)
        {
            sum+=abs(startIndex-temp[index]); // �����ƶ��ŵ���
            cout<<temp[index]<<" ";
            startIndex=temp[index];
            index--;
        }
        temp.erase(temp.begin(),temp.begin()+i+1); // ɾ���Ѿ����ʵĴŵ�
        opreational=!opreational; // �ı�ɨ�跽��
        sum+=oneWayScan(temp,startIndex,opreational); // ��������ɨ����ƶ��ŵ���
    }

    cout<<endl;
    cout<<"�ƶ��ŵ�����"<<sum<<endl;
    cout<<"ƽ��Ѱ�����ȣ�"<<(double)sum/request.size()<<endl;
}

void diskScheduling::C_SCAN(int ss,bool opreation)
{
    startIndex=ss;
    int sum=0;
    cout<<"ѭ��ɨ���㷨��"<<endl;
    cout<<"��ͷ��ʼλ�ã�"<<startIndex<<endl;
    cout<<"�ŵ��������У�";
    vector<int> temp=request;
    sort(temp.begin(),temp.end()); // ��������������
    int index=0,i;
    if(opreation)
    {
        for(i=0;i<temp.size();i++)
        {
            if(temp[i]>=startIndex) // �ҵ���һ�����ڵ��ڴ�ͷλ�õĴŵ�
            {
                index=i;
                break;
            }
        }
        while(index<temp.size())
        {
            sum+=abs(startIndex-temp[index]); // �����ƶ��ŵ���
            cout<<temp[index]<<" ";
            startIndex=temp[index];
            index++;
        }
        temp.resize(i); // ɾ���Ѿ����ʵĴŵ�
        sum+=oneWayScan(temp,startIndex,opreation); // ��������ɨ����ƶ��ŵ���
    }
    else
    {
        int i;
        for(i=temp.size()-1;i>=0;i--)
        {
            if(temp[i]<=startIndex) // �ҵ���һ��С�ڵ��ڴ�ͷλ�õĴŵ�
            {
                index=i;
                break;
            }
        }
        while(index>=0)
        {
            sum+=abs(startIndex-temp[index]); // �����ƶ��ŵ���
            cout<<temp[index]<<" ";
            startIndex=temp[index];
            index--;
        }
        temp.erase(temp.begin(),temp.begin()+i+1); // ɾ���Ѿ����ʵĴŵ�
        sum+=oneWayScan(temp,startIndex,opreation); // ��������ɨ����ƶ��ŵ���
    }

    cout<<"�ƶ��ŵ�����"<<sum<<endl;
    cout<<"ƽ��Ѱ�����ȣ�"<<(double)sum/request.size()<<endl;
}

int main()
{
    diskScheduling ds(100);
    cout<<"------------------FCFS------------------"<<endl;
    ds.FCFS();
    cout<<"------------------SSTF------------------"<<endl;
    ds.SSTF();
    cout<<"------------------SCAN------------------"<<endl;
    ds.SCAN();
    cout<<"------------------CSCAN------------------"<<endl;
    ds.C_SCAN();
    return 0;
}

// 55 58 39 18 90 160 150 38 184