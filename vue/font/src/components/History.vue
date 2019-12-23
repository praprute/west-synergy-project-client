<template>
<div>
<header-navbar></header-navbar>
<br/>
<br/>
<br/>
<br/>
<br/>
<button @click="test()">xxxx</button>
<b-container>
    {{node}}
    <line-chart 
    :data = chartdata>
    </line-chart>
</b-container>
</div>
</template>
<script>
import axios from 'axios'

export default {
    data(){
        return {
            tt:{},
            node: this.$store.state.idnode,
            chartdata:[
            //{name: 'Workout', data: {'2017-01-01 00:00:00 -0800': 3, '2017-01-02 00:00:00 -0800': 4}},
            //{name: 'Call parents', data: {'2017-01-01 00:00:00 -0800': 5, '2017-01-02 00:00:00 -0800': 3}}
            ],
            
            nulldata:{},
            datenow : "2019-12-21 16:03:06",
	        dateBefore:"2019-12-18 22:22:34",
	        idnode:"11"
        }
    },
    methods:{
        test(){
            // let data_raw = ['2017-01-01 00:00:00 -0800', '2017-01-02 00:00:00 -0800' , '2017-01-03 00:00:00 -0800']
            // let val_raw = [3,4,5]

            // var dat = {};

            // for (let i = 0; i < data_raw.length; i++) {
            //     dat[data_raw[i]] = val_raw[i]
            // }
            // /* eslint-disable no-console */
            // console.log(data_raw.length)
            // console.log(dat)

            // var xx = {}

            // xx['name'] = "WO";
            // xx['data'] = dat;

            // console.log(xx)

            // var data = []
            // data.push(xx);

            // console.log(data)
            // /* eslint-enable no-console */
            // this.tt = dat
            // // var data_buffer = {name: 'Workout', data: {'2017-01-01 00:00:00 -0800': 3, '2017-01-02 00:00:00 -0800': 4}}
            
        },
        loadHistory(){
            axios
              .post("http://localhost:3020/history",{
                  datenow:this.datenow,
	              dateBefore:this.dateBefore,
	              idnode:this.idnode
              })
              .then(response => {
                  if(response.data.success == "success"){
                          let data_raw = []
                          let val_raw  = [] 
                          let id_node  = {} 
                      for(let i = 0; i < response.data.message.length; i++){
                          data_raw.push(response.data.message[i].timestamp)
                          id_node['name'] = response.data.message[i].id_node
                      }
                      for(let j = 0; j < response.data.message.length; j++){
                          val_raw.push(response.data.message[j].sensor)
                      }
                      for (let k = 0;  k < data_raw.length; k++) {     
                          this.nulldata[data_raw[k]] = val_raw[k]      
                      }
                      id_node['data'] = this.nulldata
                      this.chartdata.push(id_node)
                      /* eslint-disable no-console */
                        console.log(this.chartdata)
                      /* eslint-enable no-console */
                  }
              })
            
            
                
            
        },
        
        loadChart(){

        }

    },
    mounted(){
        this.loadHistory();
    }
}
</script>

<style lang="css" >

</style>