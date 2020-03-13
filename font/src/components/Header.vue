<template>

  <b-navbar toggleable="lg" type="dark" variant="info">
    <b-container>
    <b-navbar-brand  href="/">WASTE SYNERGY</b-navbar-brand>
    </b-container>
  </b-navbar>
  
</template>

<script>
export default {
    data(){
      return{

      };
    },
    methods:{
      // lookhistory(){
      //   this.$router.push("/history")
      // }
       firstpage(){
         this.$router.push("/")
    }
    }


// <b-navbar-toggle target="nav-collapse"></b-navbar-toggle>

//     <b-collapse id="nav-collapse" is-nav >
//       <b-navbar-nav class="ml-auto">
//         <b-nav-item href="#">Realtime</b-nav-item>
//         <b-nav-item href="#">History</b-nav-item>
//       </b-navbar-nav>
//     </b-collapse>

}
</script>

<style lang="css" >

a.nav-link{
  color: #ffffff !important;
}

</style>


128.199.161.aaaaa137