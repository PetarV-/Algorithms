 #include<bits/stdc++.h>
#include<windows.h>
#define fr(a,i) for(int i=0;i<a;i++)
using namespace std;



class Graph {

  private:
      int Gid;
  protected:
        struct node {
            vector<node*> links;
            int id;
            string data;
            bool visited;
        };

    vector<node*> vertices;

  public:

    node * newNode(string x) {
        node *temp = new node;
        temp->data = x;
        temp->id = Gid++;
        temp->visited = false;
        vertices.push_back(temp);
        return temp;
    }

    void unvisit() {
        fr(vertices.size(), i) {
            vertices[i]->visited = false;
        }
    }
    int unvisitedVertices() {


        fr(vertices.size(), i) {
            if(vertices[i]->visited == false) {
                return i;
            }
        }
        return -1;
    }

    inline bool linkNotPresent( vector<node*> links, node *blink) {
        bool notfound = true;
        fr(links.size(),i) {
            if(links[i] == blink )
                notfound = false;
        }
        return notfound;
    }

    int addEdge( string a, string b) {
        node *anode,*bnode;
        bool af=false,bf=false;
        fr(vertices.size(),i) {
            if( vertices[i]->data == a ) {
                anode = vertices[i];
                af =true;
            }
            if( vertices[i]->data == b ) {
                bnode = vertices[i];
                bf =true;
            }
            if( af && bf ) {
                break;
            }
        }

        if( !(anode &&  bnode) ) {
            return -1;
        }

        if(linkNotPresent( anode->links, bnode) ) {
            anode->links.push_back(bnode);
        }
        return 1;
    }

    void printList() {
        fr( vertices.size(), i) {
            cout<<vertices[i]->data<<" --->  ";
            fr( vertices[i]->links.size(), j) {
                cout<<vertices[i]->links[j]->data<<" , ";
            }
            cout<<"\n";
        }
    }

    void printDFS(node *temp = NULL) {
        stack<node*> nodeStack;
         if(!temp) {
            unvisit();
            while(unvisitedVertices() != -1) {
                int unvisitedVertice = unvisitedVertices();
                printDFS(vertices[ unvisitedVertice ] );
            }
        }
        else {
            nodeStack.push(temp);
            while(!nodeStack.empty()) {
                node *temp = nodeStack.top();
                if(!temp->visited)
                    cout<<temp->data<<" ";
                temp->visited = true;
                nodeStack.pop();
                fr( temp->links.size(), i) {
                    if(!temp->links[i]->visited) {
                        nodeStack.push(temp->links[i]);
                     //   temp->links[i]->visited = true;
                    }
                }
            }
        }
    }

    void printBFS(node *temp = NULL) {
        queue<node*> nodeQueue;

        if(!temp) {
            unvisit();
            while(unvisitedVertices() != -1) {
                int unvisitedVertice = unvisitedVertices();
                printBFS(vertices[ unvisitedVertice ] );
            }
        }
        else {
            nodeQueue.push(temp);
            while(!nodeQueue.empty()) {
                node *temp = nodeQueue.front();
                if(!temp->visited)
                    cout<<temp->data<<" ";
                temp->visited = true;
                nodeQueue.pop();
                fr( temp->links.size(), i){
                    if(!temp->links[i]->visited) {
                        nodeQueue.push(temp->links[i]);
                      //  temp->links[i]->visited = true;
                    }
                }
            }
        }
    }

    Graph() {
        Gid = 0;
    }

};

int main() {
    Graph facebook;
    facebook.newNode("1");
    facebook.newNode("2");
    facebook.newNode("3");
    facebook.newNode("4");
    facebook.newNode("5");
    facebook.newNode("6");
    facebook.newNode("7");
    //facebook.newNode("sirvani");
    facebook.addEdge("1","2"); facebook.addEdge("2","1");
    facebook.addEdge("3","4");

    cout<<" \n list \n";
    facebook.printList();
    cout<<" \n bfs \n";
    facebook.printBFS();
    cout<<" \n dfs \n";
    facebook.printDFS();
    return 0;
}
