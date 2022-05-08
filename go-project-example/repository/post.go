package repository

import (
	"encoding/json"
	"os"
	"sync"
	"time"
)

type Post struct {
	Id         int64  `json:"id"`
	ParentId   int64  `json:"parent_id"`
	Content    string `json:"content"`
	CreateTime int64  `json:"create_time"`
}
type PostDao struct {
}

var (
	postDao  *PostDao
	postOnce sync.Once
)

func NewPostDaoInstance() *PostDao {
	postOnce.Do(
		func() {
			postDao = &PostDao{}
		})
	return postDao
}

func (*PostDao) QueryPostsByParentId(parentId int64) []*Post {
	postList, _ := postIndexRWMap.Get(parentId)
	return postList
}

func (*PostDao) AddNewPost(postList []*Post, id int64) error {
	for _, post := range postList {
		post.ParentId = id
		post.CreateTime = time.Now().Unix()
	}
	postIndexRWMap.Set(id, postList)
	f, err := os.OpenFile("./data/post", os.O_APPEND|os.O_WRONLY|os.O_CREATE, 0600)
	if err != nil {
		return err
	}
	defer f.Close()

	var b []byte
	for _, post := range postList {
		f.WriteString("\n")
		b, _ = json.Marshal(post)
		_, err = f.Write(b)
		if err != nil {
			return err
		}
	}

	return nil
}
