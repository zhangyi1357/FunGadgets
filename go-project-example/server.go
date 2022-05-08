package main

import (
	"encoding/json"
	"log"
	"net/http"
	"os"

	"github.com/Moonlight-Zhao/go-project-example/cotroller"
	"github.com/Moonlight-Zhao/go-project-example/repository"
	"github.com/Moonlight-Zhao/go-project-example/service"
	"gopkg.in/gin-gonic/gin.v1"
)

func main() {
	if err := Init("./data/"); err != nil {
		os.Exit(-1)
	}
	r := gin.Default()
	r.GET("/community/page/get/:id", func(c *gin.Context) {
		topicId := c.Param("id")
		data := cotroller.QueryPageInfo(topicId)
		c.JSON(200, data)
	})
	r.POST("/community/page/post", func(c *gin.Context) {
		b, err := c.GetRawData()
		if err != nil {
			log.Println("GetRawData() failed")
			c.JSON(http.StatusBadRequest, nil)
			return
		}
		var pageInfo service.PageInfo
		err = json.Unmarshal(b, &pageInfo)
		if err != nil {
			log.Println("Unmarshal() failed")
			c.JSON(http.StatusBadRequest, nil)
			return
		}
		pageData := cotroller.AddNewPage(&pageInfo)
		c.IndentedJSON(200, pageData)
	})
	err := r.Run()
	if err != nil {
		return
	}
}

func Init(filePath string) error {
	if err := repository.Init(filePath); err != nil {
		return err
	}
	return nil
}
