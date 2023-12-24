#include "Chaining.h"
using namespace std;

void Chaining::merge(vector<int> &v, int l, int m, int r)
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
  int k = l;
  while (idx < a && jdx < b)
  {
    if (left[idx] <= right[jdx])
    {
      v[k] = left[idx];
      idx++;
    }
    else
    {
      v[k] = right[jdx];
      jdx++;
    }
    k++;
  }
  while (idx < a)
  {
    v[k] = left[idx];
    k++;
    idx++;
  }
  while (jdx < b)
  {
    v[k] = right[jdx];
    k++;
    jdx++;
  }
}

void Chaining::ms(vector<int> &v, int l, int r)
{
  if (l < r && l >= 0 && r < v.size())
  {
    int m = (r - l) / 2 + l;
    ms(v, l, m);
    ms(v, m + 1, r);
    merge(v, l, m, r);
  }
}

void Chaining::createAccount(string id, int count)
{
  Account acc1;
  acc1.id = id;
  acc1.balance = count;
  dbs++;
  if (univ == true)
  { // for one-time resizing;
    bankStorage2d.resize(10103);
    univ = false;
  }
  int idx = hash(id);
  bankStorage2d[idx].push_back(acc1);
}

// IMPLEMENT YOUR CODE HERE

int Chaining::getBalance(string id)
{
  if (doesExist(id) == true)
  {
    int idx = hash(id);
    for (int i = 0; i < bankStorage2d[idx].size(); i++)
    {
      if (bankStorage2d[idx][i].id == id)
      {
        return bankStorage2d[idx][i].balance;
      }
    }
    return -1;
  }
  else
  {
    // IMPLEMENT YOUR CODE HERE
    return -1;
  }
  return -1; // Placeholder return value
}

void Chaining::addTransaction(string id, int count)
{
  if (doesExist(id) == false)
  {
    createAccount(id, count);
    return;
  }
  else
  {
    int idx = hash(id);
    for (int i = 0; i < bankStorage2d[idx].size(); i++)
    {
      if (bankStorage2d[idx][i].id == id)
      {
        bankStorage2d[idx][i].balance = bankStorage2d[idx][i].balance + count;
        return;
        // deleteAccount(bankStorage2d[idx][i].id);
        // createAccount(id, b + count);
      }
    }
  }

  // IMPLEMENT YOUR CODE HERE
}

bool Chaining::doesExist(string id)
{
  int idx = hash(id);
  bool doesExist = false;
  if(bankStorage2d.size()==0){return false ;}
  if (bankStorage2d[idx].size() == 0)
  {
    return false;
  }
  for (int i = 0; i < bankStorage2d[idx].size(); i++)
  {
    if (bankStorage2d[idx][i].id == id)
    {
      doesExist = true;
      break;
    }
  }
  if (doesExist == true)
  {
    return true;
  }
  else
  {
    return false;
  }

  // IMPLEMENT YOUR CODE HERE
  return false; // Placeholder return value
}

bool Chaining::deleteAccount(string id)
{
  if (doesExist(id) == true)
  {
    int idx = hash(id);
    dbs = dbs - 1;
    for (int i = 0; i < bankStorage2d[idx].size(); i++)
    {
      if (bankStorage2d[idx][i].id == id)
      {
        bankStorage2d[idx].erase(bankStorage2d[idx].begin() + i);
        return true;
      }
    }
  }
  else
  {
    // IMPLEMENT YOUR CODE HERE
    return false;
  }
  return false; // Placeholder return value
}
int Chaining::databaseSize() { return dbs; }
// IMPLEMENT YOUR CODE HERE
// return 0; // Placeholder return value

int Chaining::hash(string id)
{
  int hf = 0;
  int k = 1;
  for (char c : id)
  {
    hf = hf + k * (c + 1);
    k++;
  }
  return hf % 10103;

  // IMPLEMENT YOUR CODE HERE
  // Placeholder return value
}

vector<int> Chaining::getTopK(int k)
{
  if(bankStorage2d.size() ==0) {return {} ;}
  vector<int> v1;

  for (int idx = 0; idx < 10103; idx++)
  {
    for (int j = 0; j < bankStorage2d[idx].size(); j++)
    {
      v1.push_back(bankStorage2d[idx][j].balance);
    }
  }
  ms(v1, 0, dbs - 1);
  vector<int> topK;
  for (int i = dbs - 1; i >= dbs - k && i >= 0; i--)
  {
    topK.push_back(v1[i]);
  }
  return topK;
}
