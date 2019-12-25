<template>
<div class="hostory-page">
    <div class="background-histpry">

<header-navbar></header-navbar>
<b-container>
    
<div class="input-date">
    <b-row class="row-input-date">
        
        <h4 class="h4-datebefore">วันที่   </h4>
        <datepicker class="inputdate-before" v-model="dateBefore"></datepicker>
        <h4 class="h4-datenoe">  ถึงวันที่   </h4>
        <datepicker class="inputdate-now" v-model="datenow"></datepicker>
        <b-button class="button-date" variant="info" @click="loadHistory()">ตกลง</b-button>
        
         
    </b-row>

</div>
    <area-chart
    :data = chartdata>
    </area-chart>

    <!-- {{idnode}}
    {{dateBefore}}
    {{datenow}}
    {{chartdata}} -->
    
</b-container>
</div>
</div>
</template>
<script>
import axios from 'axios'
import Datepicker from 'vuejs-datepicker';


export default {
    components: {
    Datepicker
  },
    
    data(){
        return {
            tt:{},
            //node: this.$store.state.idnode,
            chartdata:[
            //{name: 'Workout', data: {'2017-01-01 00:00:00 -0800': 3, '2017-01-02 00:00:00 -0800': 4}},
            //{name: 'Call parents', data: {'2017-01-01 00:00:00 -0800': 5, '2017-01-02 00:00:00 -0800': 3}}
            ],
            
            nulldata:{},
            datenow : null,//"2019-12-23 15:02:39",
	        dateBefore: null,//"2019-12-23 12:41:50",
            idnode:this.$store.state.node_id,
            data_raw:[],
            val_raw:[], 
            id_node:{}
        }
    },
    methods:{
        ClearHistory(){
            //  this.data_raw = []
            //  this.val_raw  = []
            //  this.id_node  = {} 
            //  this.chartdata = []
            //  this.datenow = null
            //  this.dateBefore = null
             //this.nulldata = []

             this.data_raw.splice(0,1)
             this.val_raw.splice(0,1)
             this.id_node  = {}
             this.chartdata.splice(0,1)
             this.nulldata.splice(0,1)
        },
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
                          this.data_raw =[]
                          this.val_raw = []
                          this.id_node  = {}
                          this.chartdata = []
                          this.nulldata  = {}
                      for(let i = 0; i < response.data.message.length; i++){
                          this.data_raw.push(response.data.message[i].timestamp)
                          this.id_node['name'] = "node : "+response.data.message[i].node_name


                          this.val_raw.push(response.data.message[i].sensor)//test
                      }
                    //   for(let j = 0; j < response.data.message.length; j++){
                    //       this.val_raw.push(response.data.message[j].sensor)
                    //   }

                      for (let k = 0;  k < this.data_raw.length; k++) {     
                          this.nulldata[this.data_raw[k]] = this.val_raw[k]      
                      }
                      this.id_node['data'] = this.nulldata
                      this.chartdata.push(this.id_node)
                      /* eslint-disable no-console */
                        console.log(this.chartdata)
                      /* eslint-enable no-console */
                      
                  }
              })       
            
        }

    }
}
</script>

<style lang="css" >
.input-date{
    
     width: 100%;
     margin-bottom: 9%;
    margin-top: 9%; 
}

div.row.row-input-date{
    margin-top: 5%; 
    margin-bottom: 5%; 
}

input.vdatetime-input{
    margin-right: 5%;
}

h4.h4-datebefore{
    margin-left: 5%;
    margin-right: 2%;
}
h4.h4-datenoe{
    margin-left: 5%;
    margin-right: 2%;
}

div.vdatetime.inputdate-now{
    margin-right: 3%;
}

button.btn.button-date{
    margin-top: -0.5%;
    margin-left: 3%;
}

.hostory-page{
    width: 100%;
    height: 1000px;
}

.background-histpry{
    background: url('./../img/745.jpg');
    background-repeat: no-repeat;
    background-position: center center;
    background-attachment: fixed;
    -o-background-size: 100% 100%, auto;
    -moz-background-size: 100% 100%, auto;
    -webkit-background-size: 100% 100%, auto;
    background-size: 100% 100%, auto;
    position: relative;
    width: 100%;
    height: 100%;
}
</style>