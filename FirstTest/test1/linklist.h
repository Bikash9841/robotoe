
#define Max_len 12

template <class ItemType>
class LinkList
{
  public:
    int length = 0;
    ItemType data[Max_len];

    void insert(ItemType item) //link list ma value halne
    {

      data[length] = item;
      length++;
    }

    bool containsAll(LinkList l) //yesle chai duita linklist compare grne
    {
      int result = 0; //if result=this.length() then true
      if (this->length > l.length)
      {
        return false;
      }
      for (int i = 0; i < this->length; i++)
      {
        for (int j = 0; j < l.length; j++)
        {
          if (this->data[i] == l.data[j])
          {

            result++;
          }
        }
      }
      if (result == this->length)
      {
        return true;
      }
      else
      {
        return false;
      }
    }

    bool contains(int v)
    {
      for (int i = 0; i < this->length; i++)
      {
        if (this->data[i] == v)
        {
          return true;
        }
      }
      return false;
    }
};
