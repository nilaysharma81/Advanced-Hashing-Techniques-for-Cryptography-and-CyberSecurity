#include "LinearProbing.h"
using namespace std;

void LinearProbing::merge(vector<int> &v, int l, int m, int r)
{
  int a = m - l + 1;
  int b = r - m;
  vector<int> left(a);
  vector<int> right(b);
  for (int idx = 0; idx < b; idx++)
  {
    right[idx] = v[m + idx + 1];
  }
  for (int jdx = 0; jdx < a; jdx++)
  {
    left[jdx] = v[l + jdx];
  }
  int idx = 0;
  int jdx = 0;
  int kdx = l;
  while (idx < a && jdx < b)
  {
    if (left[idx] <= right[jdx])
    {
      v[kdx] = left[idx];
      idx++;
    }
    else
    {
      v[kdx] = right[jdx];
      jdx++;
    }
    kdx++;
  }
  while (idx < a)
  {
    v[kdx] = left[idx];
    kdx++;
    idx++;
  }
  while (jdx < b)
  {
    v[kdx] = right[jdx];
    kdx++;
    jdx++;
  }
}

void LinearProbing::ms(vector<int> &v, int l, int r)
{
  if (l < r && l >= 0 && r < v.size())
  {
    int m = (r - l) / 2 + l;
    ms(v, l, m);
    ms(v, m + 1, r);
    merge(v, l, m, r);
  }
}

void LinearProbing::createAccount(string id, int count)
{
  // cout<<"Here"<<endl;
  // IMPLEMENT YOUR CODE HERE
  Account acc1;
  acc1.id = id;
  acc1.balance = count;
  dbs = dbs + 1;
  if (univ == true)
  {
    bankStorage1d.resize(100000);
    univ = false;
  }
  int idx = hash(id);
  // while (doesExist(idx)==true){
  //  idx=idx+1;}
  // bankStorage1d[idx] = acc1;
  if (bankStorage1d[idx].id == "")
  {
    bankStorage1d[idx] = acc1;
  }
  else
  {
    int i = (idx + 1) % 100000;
    while (bankStorage1d[i].id != "")
    {
      i = (i + 1) % 100000;
    }
    bankStorage1d[i] = acc1;
  }
}

vector<int> LinearProbing::getTopK(int k)
{
  vector<int> v1;
  for (int i = 0; i < bankStorage1d.size(); i++)
  {
    if (bankStorage1d[i].id != "")
    {
      v1.push_back(bankStorage1d[i].balance);
    }
  }
  ms(v1, 0, dbs - 1);
  vector<int> TopK;
  for (int i = dbs - 1; i >= dbs - k && i>=0; i--)
  {
    TopK.push_back(v1[i]);
  }
  return TopK;
}

// int LinearProbing::getBalance(string id) {
//   if (doesExist(id)==false) {
//     return -1;
//   } else {
//     int idx = hash(id);
//     for (int i = idx; i < bankStorage1d.size(); i++) {
//       if (bankStorage1d[i].id == id) {
//         return bankStorage1d[i].balance;
//       }
//     }
//     return -1;
//     // IMPLEMENT YOUR CODE HERE}
//     // Placeholder return value
//   }
// }

int LinearProbing::getBalance(string id)
{
  if (doesExist(id) == true)
  {
    int idx = hash(id);
    for (int i = idx; i < bankStorage1d.size(); i = (i + 1) % 100000)
    {
      if (bankStorage1d[i].id == id)
      {
        return bankStorage1d[i].balance;
      }
    }
  }
  else
  {
    return -1;
  }
  return -1;
  // IMPLEMENT YOUR CODE HERE}
  // Placeholder return value
}

void LinearProbing::addTransaction(string id, int count)
{
  if (doesExist(id) == false)
  {
    createAccount(id, count);
  }
  else
  {
    int idx = hash(id);
    for (int i = idx; i < bankStorage1d.size(); i = (i + 1) % 100000)
    {
      if (bankStorage1d[i].id == id)
      {
        int b = bankStorage1d[i].balance;
        deleteAccount(bankStorage1d[i].id);
        createAccount(id, b + count);
        break;
      }
    }
    // IMPLEMENT YOUR CODE HERE
  }
}

bool LinearProbing::doesExist(string id)
{
  int idx = hash(id);
  int kounter = 0;

  for (int i = idx; i < bankStorage1d.size() && kounter <= bankStorage1d.size() +3; i = (i + 1) % 100000)
  {
    kounter++;
    if (bankStorage1d[i].id == id)
    {
      return true;
      break;
    }
  }
  // IMPLEMENT YOUR CODE HERE
  return false; // Placeholder return value
}

bool LinearProbing::deleteAccount(string id)
{
  if (doesExist(id) == false)
  {
    return false;
  }
  else
  {
    int idx = hash(id);
    for (int i = idx; i < bankStorage1d.size(); i = (i + 1) % 100000)
    {
      if (bankStorage1d[i].id == id)
      {
        dbs = dbs - 1;
        bankStorage1d[i].balance = 0;
        bankStorage1d[i].id = ""; // resetting that id.
        return true;
      }
    }
  }
  // IMPLEMENT YOUR CODE HERE
  return false; // Placeholder return value
}
int LinearProbing::databaseSize()
{
  return dbs;
  // IMPLEMENT YOUR CODE HERE
  // return 0; // Placeholder return value
}

int LinearProbing::hash(string id)
{
  int hf = 0;
  int k = 1;
  for (char c : id)
  {
    hf = (hf + k * (c+1))%100000;
    k++;
  }
  return hf % 100000;
  // IMPLEMENT YOUR CODE HERE
  // Placeholder return value
}

// int main()
// {
//   LinearProbing chobj;
//     string x;
//     while(cin>>x)
//     {
//         if(x=="createAccount")
//         {
//             string id;
//             int count;
//             cin>>id>>count;
//             chobj.createAccount(id,count);
//         }
//         else if(x=="databaseSize")
//             cout<<chobj.databaseSize()<<endl;
//         else if(x=="getTopK")
//         {
//             int k;
//             cin>>k;
//             for(auto i:chobj.getTopK(k))
//                 cout<<i<<" ";
//             cout<<endl;
//         }
//         else if(x=="addTransaction")
//         {
//             string id;
//             int count;
//             cin>>id>>count;
//             chobj.addTransaction(id,count);
//         }
//         else if(x=="getBalance")
//         {
//             string id;
//             cin>>id;
//             cout<<chobj.getBalance(id)<<endl;
//         }
//         else if(x=="deleteAccount")
//         {
//             string id;
//             cin>>id;
//             chobj.deleteAccount(id);
//         }
//     }
// }