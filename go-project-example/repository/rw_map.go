// 以下实现参考《Go 并发之三种线程安全的 map - AFreeCoder的文章 - 知乎》
// 链接: https://zhuanlan.zhihu.com/p/356739568
package repository

import "sync"

type RWTopicMap struct {
	sync.RWMutex
	m map[int64]*Topic
}

func NewRWTopicMap(m map[int64]*Topic) *RWTopicMap {
	return &RWTopicMap{
		m: m,
	}
}

func (m *RWTopicMap) Get(k int64) (*Topic, bool) {
	m.RLock()
	defer m.RUnlock()
	v, existed := m.m[k]
	return v, existed
}

func (m *RWTopicMap) Set(k int64, v *Topic) {
	m.Lock()
	defer m.Unlock()
	m.m[k] = v
}

type RWPostMap struct {
	sync.RWMutex
	m map[int64][]*Post
}

func NewRWPostMap(m map[int64][]*Post) *RWPostMap {
	return &RWPostMap{
		m: m,
	}
}

func (m *RWPostMap) Get(k int64) ([]*Post, bool) {
	m.RLock()
	defer m.RUnlock()
	v, existed := m.m[k]
	return v, existed
}

func (m *RWPostMap) Set(k int64, v []*Post) {
	m.Lock()
	defer m.Unlock()
	m.m[k] = v
}
