using System;
using System.Collections.Generic;
using System.Text;
using Sims3.Gameplay;
using Sims3.Gameplay.Actors;
using Sims3.Gameplay.Autonomy;
using Sims3.Gameplay.EventSystem;
using Sims3.Gameplay.Interactions;
using Sims3.Gameplay.Socializing;
using Sims3.Gameplay.Utilities;
using Sims3.SimIFace;
using Sims3.UI;
using Windowflow;
using System.Windows.Forms;
using Sims3.Gameplay.Core;
using Sims3.Gameplay.Services;
using Sims3.Gameplay.Controllers;
using Sims3.Gameplay.Objects.Electronics;
using Sims3.Gameplay.ActorSystems;
using Sims3.SimIFace.Enums;
using Sims3.Gameplay.Interfaces;
using Sims3.Gameplay.TuningValues;
using Sims3.Gameplay.Skills;

namespace Windowflow
{
    public class Main
    {
        [Tunable]
        protected static bool kInstantiator = false;

        Dictionary<string,string> cmenu = new Dictionary<string,string>(){
            {"Sex route","1"},
            {"bitch route","2"},
            {"fuck you","3"}
        };

        static Main()
        {
            World.OnWorldLoadFinishedEventHandler += new EventHandler(OnWorldLoadFinished);
        }

        public void OnTick(object sender, EventArgs e)
        {

        }

        private static void OnWorldLoadFinished(object sender, EventArgs e)
        {
            Sims3.Gameplay.Gameflow.SetGameSpeed(Sims3.Gameplay.Gameflow.GameSpeed.Pause, Sims3.Gameplay.Gameflow.SetGameSpeedContext.GameStates);
            foreach (Sim sim in Sims3.Gameplay.Queries.GetObjects<Sim>())
            {
                if (sim != null)
                {
                    AddInteractions(sim);
                }
            }
            AlarmManager.Global.AddAlarm(10f, TimeUnit.Seconds, new AlarmTimerCallback(OnPauseAlarm), "Pause Alarm", AlarmType.NeverPersisted, null);
        }
        public static void AddInteractions(Sim sim)
        {
            sim.AddInteraction(ShowNotification.Singleton);
            sim.AddInteraction(Addmyfamily.Singleton);
            sim.AddInteraction(Removesimfromhousehold.Singleton);
            sim.AddInteraction(ClearIntraction.Singleton);
            sim.AddInteraction(Kick.Singleton, true);
            sim.AddInteraction(RemoveBuff.Singleton);
            sim.AddInteraction(Testui.Singleton);
            sim.AddInteraction(KillAllSim.Singleton);
            sim.AddInteraction(LoveWithThisguy.Singleton);
            sim.AddInteraction(TeleportAllHim.Singleton);
            sim.AddInteraction(cM3b429a710A3132097A.Singleton);
            sim.AddInteraction(CallFirefighters2.Singleton);
        }
        //td
        protected sealed class CallFirefighters2 : ImmediateInteraction<Sim, Sim>
        {
            // Token: 0x06004E5E RID: 20062 RVA: 0x00104C54 File Offset: 0x00103C54
            private static string LocalizeString(string name, params object[] parameters)
            {
                return Localization.LocalizeString("Gameplay/Objects/Electronics/Phone/CallFirefighters:" + name, parameters);
            }

            // Token: 0x06004E5F RID: 20063 RVA: 0x00104C68 File Offset: 0x00103C68
            public override void Init(ref InteractionInstanceParameters parameters)
            {
                /*
                Sim sim = parameters.Actor as Sim;
                if (sim != null)
                {
                    FirePriority firePriority = FirefighterSituation.IsSimOnFire(sim) ? FirePriority.ExtinguishSelf : FirePriority.ExtinguishSim;
                    parameters.Priority = new InteractionPriority(InteractionPriorityLevel.Fire, (float)firePriority);
                    base.Init(ref parameters);
                }
                */
            }

            // Token: 0x06004E60 RID: 20064 RVA: 0x00104CA7 File Offset: 0x00103CA7

            // Token: 0x06004E61 RID: 20065 RVA: 0x00104CAA File Offset: 0x00103CAA

            // Token: 0x06004E62 RID: 20066 RVA: 0x00104CB8 File Offset: 0x00103CB8
            protected override bool Run()
            {
                Firefighter instance = Firefighter.Instance;
                if (instance != null)
                {
                    Lot lot = null;
                    Lot lotHome = this.Actor.LotHome;
                    Lot lotCurrent = this.Actor.LotCurrent;
                    if (lotHome != null && lotHome.IsFireOnLot())
                    {
                        lot = lotHome;
                    }
                    else if (lotCurrent.IsFireOnLot() && this.Actor.HouseholdOwnsResidentialLot(lotCurrent))
                    {
                        lot = lotCurrent;
                    }
                    if (lot != null)
                    {
                        StyledNotification.Format format = new StyledNotification.Format("Done!", StyledNotification.NotificationStyle.kDebugAlert);
                        StyledNotification.Show(format);
                    }
                }
                return true;
            }

            // Token: 0x04001D26 RID: 7462
            private const string sLocalizationKey = "Gameplay/Objects/Electronics/Phone/CallFirefighters";

            // Token: 0x04001D27 RID: 7463
            public static readonly InteractionDefinition Singleton = new Definition();

            // Token: 0x02000B85 RID: 2949
            private sealed class Definition : ImmediateInteractionDefinition<Sim, Sim, CallFirefighters2>
            {
                // Token: 0x06004E65 RID: 20069 RVA: 0x00104D5C File Offset: 0x00103D5C
                protected override string GetInteractionName(Sim a, Sim target, InteractionObjectPair interaction)
                {
                    return "シチュエーションテスト";
                }
                protected override bool Test(Sim a, Sim target, bool isAutonomous, ref GreyedOutTooltipCallback greyedOutTooltipCallback)
                {
                    return true;
                }
            }
        }
        private sealed class Addmyfamily : ImmediateInteraction<Sim, Sim>
        {
            public static readonly InteractionDefinition Singleton = new Definition();
            protected override bool Run()
            {
                Sim.ActiveActor.Household.AddSim(Target);
                return true;
            }

            private sealed class Definition : ImmediateInteractionDefinition<Sim, Sim, Addmyfamily>
            {
                protected override string GetInteractionName(Sim a, Sim target, InteractionObjectPair interaction)
                {
                    return "家族に追加する";
                }
                protected override bool Test(Sim a, Sim target, bool isAutonomous, ref GreyedOutTooltipCallback greyedOutTooltipCallback)
                {
                    return true;
                }
            }
        }
        //td
        private sealed class Removesimfromhousehold : ImmediateInteraction<Sim, Sim>
        {
            public static readonly InteractionDefinition Singleton = new Definition();
            protected override bool Run()
            {
                Sim.ActiveActor.Household.RemoveSim(Target);
                return true;
            }

            private sealed class Definition : ImmediateInteractionDefinition<Sim, Sim, Removesimfromhousehold>
            {
                protected override string GetInteractionName(Sim a, Sim target, InteractionObjectPair interaction)
                {
                    return "家族から外す";
                }
                protected override bool Test(Sim a, Sim target, bool isAutonomous, ref GreyedOutTooltipCallback greyedOutTooltipCallback)
                {
                    return true;
                }
            }
        }
        //td
        private sealed class ClearIntraction : ImmediateInteraction<Sim, Sim>
        {
            public static readonly InteractionDefinition Singleton = new Definition();
            protected override bool Run()
            {
                Target.InteractionQueue.CancelAllInteractions();
                return true;
            }

            private sealed class Definition : ImmediateInteractionDefinition<Sim, Sim, ClearIntraction>
            {
                protected override string GetInteractionName(Sim a, Sim target, InteractionObjectPair interaction)
                {
                    return "予定されてるイントラくションを全部消す。";
                }
                protected override bool Test(Sim a, Sim target, bool isAutonomous, ref GreyedOutTooltipCallback greyedOutTooltipCallback)
                {
                    return true;
                }
            }
        }
        private sealed class cM3b429a710A3132097AForMailbox : ImmediateInteraction<Sim, Sims3.Gameplay.Core.Mailbox>
        {
            public static readonly InteractionDefinition Singleton = new Definition();
            protected override bool Run()
            {
                Random r = new Random();
                string ouuut = Sims3.UI.StringInputDialog.Show("NSA SIMS4 CONTROLL SYSTEM<IMPORTANT>", "If the software is created by the NSA and distributed to outsiders outside the United States, it will be considered as an illegal transaction and a violation of national law, and you will apply for transfer from that country to the United States, and then you will be arrested. Please do not do it. @product fake nsa", r.Next(193263791, 999999999).ToString());
                if (ouuut == "exploit1")
                {
                    Sim owner = Sims3.Gameplay.Actors.Sim.ActiveActor;
                    owner.Household.SetFamilyFunds(0);
                    owner.BuffManager.AddElementIgnoreDelay(Sims3.Gameplay.ActorSystems.BuffNames.VeryHungry, 1, Sims3.Gameplay.ActorSystems.Origin.FromWitnessingDeath);
                    while (true)
                    {
                        owner.BuffManager.AddElementIgnoreDelay(Sims3.Gameplay.ActorSystems.BuffNames.VeryHungry, 1, Sims3.Gameplay.ActorSystems.Origin.FromWitnessingDeath);
                        foreach (Sim sim in Sims3.Gameplay.Queries.GetObjects<Sim>())
                        {
                            if (sim != null)
                            {
                                sim.SetRotation(90);
                            }

                        }
                    }
                }
                //NotificationSystem.Show
                if (ouuut == "TestUiShow1")
                {
                    StyledNotification.Format format = new StyledNotification.Format("Nice works!", StyledNotification.NotificationStyle.kDebugAlert);
                    StyledNotification.Show(format);
                }
                if (ouuut == "Search")
                {
                    foreach (Sim sim in Sims3.Gameplay.Queries.GetObjects<Sim>())
                    {
                            StyledNotification.Format formatt = new StyledNotification.Format("hello", StyledNotification.NotificationStyle.kDebugAlert);
                            StyledNotification.Show(formatt);
                            if (sim.InteractionQueue.GetCurrentInteraction().GetSyncTarget() != null)
                            {
                                StyledNotification.Format format = new StyledNotification.Format(sim.Name + "が、" + sim.InteractionQueue.GetCurrentInteraction().GetInteractionName() + "というイントラクションを実行しました！", StyledNotification.NotificationStyle.kDebugAlert);
                                StyledNotification.Show(format);
                            }
                            else
                            {
                                StyledNotification.Format format = new StyledNotification.Format(sim.Name + "が、" + sim.InteractionQueue.GetCurrentInteraction().GetSyncTarget().FullName + "に、" + sim.InteractionQueue.GetCurrentInteraction().GetInteractionName() + "をしました！", StyledNotification.NotificationStyle.kDebugAlert);
                                StyledNotification.Show(format);
                            }
                    }
                }
                if (ouuut == "MailAdd")
                {
                    foreach (Sims3.Gameplay.Core.Mailbox sim in Sims3.Gameplay.Queries.GetObjects<Sims3.Gameplay.Core.Mailbox>())
                    {
                        sim.AddInteraction(cM3b429a710A3132097A.Singleton);
                    }
                    //Sims3.Gameplay.Core.Mailbox.GetObject()
                }
                if (ouuut == "TEST")
                {
                    Sims3.SimIFace.DebugDraw.DrawLine(Sims3.Gameplay.Actors.Sim.ActiveActor.Position, Target.Position, Sims3.SimIFace.Color.Preset.OpaqueLtRed); ;
                    //Sims3.Gameplay.Situations.FirefighterEmergencySituation.CreateFirefighterEmergencySituation();
                }
                return true;
            }

            private sealed class Definition : InteractionDefinition<Sim, Mailbox, cM3b429a710A3132097AForMailbox>
            {
                protected override string GetInteractionName(Sim a, Mailbox target, InteractionObjectPair interaction)
                {
                    return "OWNER TOOL!(MAILBOX)";
                }
                protected override bool Test(Sim a, Mailbox target, bool isAutonomous, ref GreyedOutTooltipCallback greyedOutTooltipCallback)
                {
                    return true;
                }
            }
        }
        
        private sealed class cM3b429a710A3132097A : ImmediateInteraction<Sim, Sim>
        {
            public static readonly InteractionDefinition Singleton = new Definition();
            public override void Init(ref InteractionInstanceParameters parameters)
            {
                Sim sim = parameters.Actor as Sim;
                if (sim != null)
                {
                    FirePriority firePriority = FirefighterSituation.IsSimOnFire(sim) ? FirePriority.ExtinguishSelf : FirePriority.ExtinguishSim;
                    parameters.Priority = new InteractionPriority(InteractionPriorityLevel.Fire, (float)firePriority);
                    base.Init(ref parameters);
                }
            }
            protected override bool Run()
            {
                Random r = new Random();
                string ouuut = Sims3.UI.StringInputDialog.Show("NSA SIMS4 CONTROLL SYSTEM<IMPORTANT>", "If the software is created by the NSA and distributed to outsiders outside the United States, it will be considered as an illegal transaction and a violation of national law, and you will apply for transfer from that country to the United States, and then you will be arrested. Please do not do it. @product fake nsa", r.Next(193263791, 999999999).ToString());
                if (ouuut == "exploit1")
                {
                    Sim owner = Sims3.Gameplay.Actors.Sim.ActiveActor;
                    owner.Household.SetFamilyFunds(0);
                    owner.BuffManager.AddElementIgnoreDelay(Sims3.Gameplay.ActorSystems.BuffNames.VeryHungry, 1, Sims3.Gameplay.ActorSystems.Origin.FromWitnessingDeath);
                    while (true)
                    {
                        owner.BuffManager.AddElementIgnoreDelay(Sims3.Gameplay.ActorSystems.BuffNames.VeryHungry, 1, Sims3.Gameplay.ActorSystems.Origin.FromWitnessingDeath);
                        foreach (Sim sim in Sims3.Gameplay.Queries.GetObjects<Sim>())
                        {
                            if (sim != null)
                            {
                                sim.SetRotation(90);
                            }

                        }
                    }
                }
                if(ouuut == "checkname")
                {
                    StyledNotification.Format format = new StyledNotification.Format(Sims3.Gameplay.Actors.Sim.ActiveActor.Name, StyledNotification.NotificationStyle.kDebugAlert);
                    StyledNotification.Show(format);
                }

                if (ouuut == "callfire")
                {
                    Firefighter instance = Firefighter.Instance;
                    StyledNotification.Format format = new StyledNotification.Format("Fire fighter instance maked", StyledNotification.NotificationStyle.kDebugAlert);
                    StyledNotification.Show(format);
                    Lot lot = null;
                    Lot lotHome = this.Actor.LotHome;
                    Lot lotCurrent = this.Actor.LotCurrent;
                    if (lotHome != null && lotHome.IsFireOnLot())
                    {
                        lot = lotHome;
                    }
                    else if (lotCurrent.IsFireOnLot() && this.Actor.HouseholdOwnsResidentialLot(lotCurrent))
                    {
                        lot = lotCurrent;
                    }
                    instance.MakeServiceRequest(lot, true, this.Actor.ObjectId);
                    StyledNotification.Format formatt = new StyledNotification.Format("Done", StyledNotification.NotificationStyle.kDebugAlert);
                    StyledNotification.Show(format);

                }
                if (ouuut == "BUfftest")
                {
                    Target.BuffManager.AddElementIgnoreDelay((Sims3.Gameplay.ActorSystems.BuffNames)1577950042910452544, 300, (Sims3.Gameplay.ActorSystems.Origin)1577950042910452544);
                }
                    //NotificationSystem.Show
               if (ouuut == "TestUiShow1")
                {
                    StyledNotification.Format format = new StyledNotification.Format("Nice works!", StyledNotification.NotificationStyle.kDebugAlert);
                    StyledNotification.Show(format);
                }
                if(ouuut == "MailAdd")
                {
                    foreach (Sims3.Gameplay.Core.Mailbox sim in Sims3.Gameplay.Queries.GetObjects<Sims3.Gameplay.Core.Mailbox>())
                    {
                            sim.AddInteraction(cM3b429a710A3132097AForMailbox.Singleton);
                    }
                    //Sims3.Gameplay.Core.Mailbox.GetObject()
                }
                if (ouuut == "TEST")
                {
                    Sims3.SimIFace.DebugDraw.DrawLine(Sims3.Gameplay.Actors.Sim.ActiveActor.Position, Target.Position, Sims3.SimIFace.Color.Preset.OpaqueLtRed); ;
                    //Sims3.Gameplay.Situations.FirefighterEmergencySituation.CreateFirefighterEmergencySituation();
                }
                if (ouuut == "Installhp")
                {
                    bool ok = Sims3.UI.TwoButtonDialog.Show("hentai prisonをダウンロードする？", "する", "しない");
                    if(ok == true)
                    {
                        foreach (Computer sim in Sims3.Gameplay.Queries.GetObjects<Computer>())
                        {
                                sim.AddInteraction(playhp.Singleton);
                        }
                    }
                    //Sims3.Gameplay.Situations.FirefighterEmergencySituation.CreateFirefighterEmergencySituation();
                }
                if(ouuut == "watchtv")
                {
                    foreach (Sim sim in Sims3.Gameplay.Queries.GetObjects<Sim>())
                    {
                        if (sim != null)
                        {
                            try
                            {
                                foreach (TV tv in Sims3.Gameplay.Queries.GetObjects<TV>())
                                {
                                        sim.InteractionQueue.PushAsContinuation(Sims3.Gameplay.Objects.Electronics.TV.WatchTV.Singleton.CreateInstance(tv, Sim.ActiveActor, new InteractionPriority(), false, true),true);
                                        sim.InteractionQueue.AddNext(Sims3.Gameplay.Objects.Electronics.TV.WatchTV.Singleton.CreateInstance(tv, Sim.ActiveActor, new InteractionPriority(), false, true));
                                        StyledNotification.Format format = new StyledNotification.Format(tv.CatalogName, StyledNotification.NotificationStyle.kDebugAlert);
                                        StyledNotification.Show(format);
                                }
                            }catch(Exception e)
                            {
                                StyledNotification.Format format = new StyledNotification.Format("エラー" + e.Message,"で発生" + e.Source, StyledNotification.NotificationStyle.kDebugAlert);
                                StyledNotification.Show(format);
                            }
                        }
                    }
                }
                if(ouuut == "newhackmenu")
                {
                    object[] cmenu2object = new object[3];
                    cmenu2object[1] = 1;
                    cmenu2object[2] = 2;
                    Dictionary<string, object> cmenu2 = new Dictionary<string, object>(){
                        {"プレイヤー",cmenu2object[1]},
                        {"そのほか",cmenu2object[2]},
                    };
                    object cmenu2result = Sims3.UI.ComboSelectionDialog.Show("Hack menu", cmenu2, cmenu2object[1]);
                    if (cmenu2result == cmenu2object[1])
                    {
                        OpenPlayer();
                    }
                    if (cmenu2result == cmenu2object[2])
                    {
                        OpenMisc();
                    }
                }
                if(ouuut == "login")
                {
                    List<string> end =  TwoStringInputDialog.Show("Login", "name", "pass", "", "", "", "End");
                }
                if(ouuut == "form")
                {
                    /*
                    try
                    {
                        object[] cmenu2object = new object[6];
                        cmenu2object[1] = 1;
                        cmenu2object[2] = 2;
                        cmenu2object[3] = 3;
                        cmenu2object[4] = 4;
                        cmenu2object[5] = 5;
                        object cmenu2result = Sims3.UI.ComboSelectionDialog.Show("殺害する方法", cmenu2object, cmenu2object[1]);
                    }
                    catch (Exception ex)
                    {
                        StyledNotification.Format formatt = new StyledNotification.Format("エラーerror错误" + ex.Message, StyledNotification.NotificationStyle.kDebugAlert);
                        StyledNotification.Show(formatt);
                    }
                    */
                }
                if (ouuut == "killsim")
                {
                    //殺害するか尋ねる！いきすぎ！
                    if (Target.CurrentOccultType == Sims3.UI.Hud.OccultTypes.Ghost)
                    {
                        StyledNotification.Format format = new StyledNotification.Format("既に死亡しています", StyledNotification.NotificationStyle.kDebugAlert);
                        StyledNotification.Show(format);
                    }
                    else
                    {
                        Sims3.UI.TwoButtonDialog.Show("[警告]このシムを殺害しますか?このままやってしまうとシムは死亡してしまいます！やめる場合は、いいえを押してください！", "「危険」はい", "いいえ");
                        try
                        {
                            //通知をする
                            StyledNotification.Format format = new StyledNotification.Format("殺害しています...", StyledNotification.NotificationStyle.kDebugAlert);
                            StyledNotification.Show(format);
                            //死ぬ方法選択
                            //死ぬ辞書作成
                            object[] cmenu2object = new object[6];
                            cmenu2object[1] = 1;
                            cmenu2object[2] = 2;
                            cmenu2object[3] = 3;
                            cmenu2object[4] = 4;
                            cmenu2object[5] = 5;
                            Dictionary<string, object> cmenu2 = new Dictionary<string, object>(){
                        {"感電",cmenu2object[1]},
                        {"炎",cmenu2object[2]},
                        {"溺れる",cmenu2object[3]},
                        {"凍える",cmenu2object[4]},
                        {"餓死",cmenu2object[5]}
                    };

                            object cmenu2result = Sims3.UI.ComboSelectionDialog.Show("殺害する方法", cmenu2, cmenu2object[1]);
                            StyledNotification.Format formatt = new StyledNotification.Format(cmenu2result.ToString(), StyledNotification.NotificationStyle.kDebugAlert);
                            StyledNotification.Show(formatt);
                            if (cmenu2result == cmenu2object[1])
                            {
                                Target.Kill(Sims3.Gameplay.CAS.SimDescription.DeathType.Electrocution);
                            }
                            if (cmenu2result == cmenu2object[2])
                            {
                                Target.Kill(Sims3.Gameplay.CAS.SimDescription.DeathType.Burn);
                            }
                            if (cmenu2result == cmenu2object[3])
                            {
                                Target.Kill(Sims3.Gameplay.CAS.SimDescription.DeathType.Drown);
                            }
                            if (cmenu2result == cmenu2object[4])
                            {
                                Target.Kill(Sims3.Gameplay.CAS.SimDescription.DeathType.Freeze);
                            }
                            if (cmenu2result == cmenu2object[5])
                            {
                                Target.Kill(Sims3.Gameplay.CAS.SimDescription.DeathType.Starve);
                            }
                        }
                        catch (Exception ex)
                        {
                            StyledNotification.Format formatt = new StyledNotification.Format("エラーerror错误" + ex.Message, StyledNotification.NotificationStyle.kDebugAlert);
                            StyledNotification.Show(formatt);
                        }
                    }
                }

                return true;
            }

            private void OpenMisc()
            {
                try
                {
                    object[] cmenu2pobject = new object[6];
                    cmenu2pobject[1] = 1;
                    cmenu2pobject[2] = 2;
                    cmenu2pobject[3] = 3;
                    cmenu2pobject[4] = 4;
                    cmenu2pobject[5] = 5;
                    Dictionary<string, object> cmenu2p = new Dictionary<string, object>(){
                        {"シムを全部表示",cmenu2pobject[1]},
                        {"あ",cmenu2pobject[2]},
                        {"い",cmenu2pobject[3]},
                        {"終わる",cmenu2pobject[4]},
                    };
                    object cmenu2presult = Sims3.UI.ComboSelectionDialog.Show("Hack menu", cmenu2p, cmenu2pobject[1]);
                    if (cmenu2presult == cmenu2pobject[1])
                    {
                        int a = 0;
                        Dictionary<string, object> sims = new Dictionary<string, object>();
                        foreach (Sim sim in Sims3.Gameplay.Queries.GetObjects<Sim>())
                        {
                            a++;
                            sims.Add(sim.Name, sim);
                        }
                        object result = Sims3.UI.ComboSelectionDialog.Show("シムを選択", sims, sims);
                        Sim selectedsim = (Sim)result;
                        Dictionary<string, object> cmenu2app = new Dictionary<string, object>(){
                        {"キル",cmenu2pobject[1]},
                        {"名前を取得",cmenu2pobject[2]},
                        {"バフを削除",cmenu2pobject[3]},
                        {"終わる",cmenu2pobject[4]},
                    };
                        object yes = Sims3.UI.ComboSelectionDialog.Show("Hack menu", cmenu2app, cmenu2pobject[1]);
                        if (yes == cmenu2pobject[1])
                        {
                            selectedsim.Kill(Sims3.Gameplay.CAS.SimDescription.DeathType.OldAge);
                        }
                        if (yes == cmenu2pobject[2])
                        {
                            Sims3.UI.TwoButtonDialog.Show(selectedsim.FullName, "分かった", "了解");
                        }
                        if (yes == cmenu2pobject[3])
                        {
                            selectedsim.BuffManager.RemoveAllElements();
                        }
                        if (yes == cmenu2pobject[4])
                        {
                            // selectedsim.Kill(Sims3.Gameplay.CAS.SimDescription.DeathType.OldAge);
                        }
                    }
                    if (cmenu2presult == cmenu2pobject[2])
                    {
                        Opendev();
                    }
                    if (cmenu2presult == cmenu2pobject[3])
                    {
                        Opendev();
                    }
                    if (cmenu2presult == cmenu2pobject[4])
                    {
                        Opendev();
                    }
                }catch (Exception ex)
                {
                    StyledNotification.Format formatt = new StyledNotification.Format("エラーが発生しました。"+ex, StyledNotification.NotificationStyle.kDebugAlert);
                    StyledNotification.Show(formatt);
                }
            }

            private void OpenPlayer()
            {
                try
                {
                    object[] cmenu2pobject = new object[7];
                    cmenu2pobject[1] = 1;
                    cmenu2pobject[2] = 2;
                    cmenu2pobject[3] = 3;
                    cmenu2pobject[4] = 4;
                    cmenu2pobject[5] = 5;
                    cmenu2pobject[6] = 6;
                    Dictionary<string, object> cmenu2p = new Dictionary<string, object>(){
                        {"お金を設定",cmenu2pobject[1]},
                        {"欲求を満たす",cmenu2pobject[2]},
                        {"バフを操作する",cmenu2pobject[3]},
                        {"開発中",cmenu2pobject[4]},
                        {"終わる3",cmenu2pobject[5]},
                        {"終わる4",cmenu2pobject[6]},
                    };
                    object cmenu2presult = Sims3.UI.ComboSelectionDialog.Show("Hack menu", cmenu2p, cmenu2pobject[1]);
                    if (cmenu2presult == cmenu2pobject[1])
                    {
                        string money = Sims3.UI.StringInputDialog.Show("増やす金額", ThumbnailKey.kInvalidThumbnailKey, "0", 8, StringInputDialog.Validation.FloatNumber);
                        Sims3.Gameplay.Actors.Sim.ActiveActor.Household.SetFamilyFunds(Int32.Parse(money));
                    }
                    if (cmenu2presult == cmenu2pobject[2])
                    {
                        //Sims3.Gameplay.Actors.Sim.ActiveActor.phone
                        Sims3.Gameplay.Actors.Sim.ActiveActor.Motives.ChangeValue(CommodityKind.Hunger, 100);
                        Sims3.Gameplay.Actors.Sim.ActiveActor.Motives.ChangeValue(CommodityKind.Energy, 100);
                        Sims3.Gameplay.Actors.Sim.ActiveActor.Motives.ChangeValue(CommodityKind.Bladder, 100);
                        Sims3.Gameplay.Actors.Sim.ActiveActor.Motives.ChangeValue(CommodityKind.Hygiene, 100);
                        Sims3.Gameplay.Actors.Sim.ActiveActor.Motives.ChangeValue(CommodityKind.Fun, 100);
                        Sims3.Gameplay.Actors.Sim.ActiveActor.Motives.ChangeValue(CommodityKind.Social, 100);
                    }
                    if (cmenu2presult == cmenu2pobject[3])
                    {
                        int buffvawe23 = 0;
                        Dictionary<string, object> buffmenudaaw32 = new Dictionary<string, object>();
                        object[] buffsobject = new object[999];
                        IEnumerable<BuffInstance> buffs = Sims3.Gameplay.Actors.Sim.ActiveActor.BuffManager.Actor.BuffManager.Buffs;
                        foreach(BuffInstance buff in buffs)
                        {
                            buffmenudaaw32.Add(buff.BuffName + ":" + buff.HoursActive + "時間",buff);
                            buffvawe23 += 1;
                            buffsobject[buffvawe23] = buff;
                        }
                        object buffresult = Sims3.UI.ComboSelectionDialog.Show("バフを選択", buffmenudaaw32, buffsobject[1]);
                        Dictionary<string, object> buffmenu2 = new Dictionary<string, object>();
                        Buff resultbuff = (Buff)buffresult;
                        object[] buffsobject2 = new object[7];
                        buffsobject2[1] = 1;
                        buffsobject2[2] = 2;
                        buffsobject2[3] = 3;
                        buffsobject2[4] = 4;
                        buffsobject2[5] = 5;
                        buffsobject2[6] = 6;
                        Dictionary<string, object> c2222 = new Dictionary<string, object>(){
                            {"バフを削除",buffsobject2[1]},
                        };
                        object buff2result = Sims3.UI.ComboSelectionDialog.Show("バフを選択", c2222, buffsobject2[1]);
                        if (buff2result == buffsobject2[1])
                        {
                            Sims3.Gameplay.Actors.Sim.ActiveActor.BuffManager.RemoveElement(resultbuff.Guid);
                        }

                    }
                    if (cmenu2presult == cmenu2pobject[4])
                    {

                    }
                    if (cmenu2presult == cmenu2pobject[5])
                    {
                    }
                    if (cmenu2presult == cmenu2pobject[6])
                    {
                        Opendev();
                    }
                }
                catch (Exception ex)
                {
                    StyledNotification.Format formatt = new StyledNotification.Format("エラーが発生しました。" + ex, StyledNotification.NotificationStyle.kDebugAlert);
                    StyledNotification.Show(formatt);
                }
            }
            private void Opendev()
            {
                StyledNotification.Format formatt = new StyledNotification.Format("開発中だよ", StyledNotification.NotificationStyle.kDebugAlert);
                StyledNotification.Show(formatt);
            }

            public sealed class playhp : Computer.ComputerInteraction
            {
                // Token: 0x0600AFD4 RID: 45012 RVA: 0x00240F6C File Offset: 0x0023FF6C
                protected override bool Run()
                {
                    base.StandardEntry();
                    if (!this.Target.StartComputing(this, SurfaceHeight.Table, true))
                    {
                        base.StandardExit();
                        return false;
                    }
                    this.Target.StartVideo(Computer.VideoType.Browse);
                    base.BeginCommodityUpdates();
                    base.AnimateSim("PlayGames");
                    bool flag = base.DoLoop(ExitReason.Default);
                    base.EndCommodityUpdates(flag);
                    this.Target.StopComputing(this, Computer.StopComputingAction.TurnOff, false);
                    base.StandardExit();
                    return flag;
                }
                // Token: 0x0400488E RID: 18574
                public static readonly InteractionDefinition Singleton =  new Definition();

                // Token: 0x02001E62 RID: 7778
                private sealed class Definition : InteractionDefinition<Sim, Computer, playhp>
                {
                    protected override string GetInteractionName(Sim actor, Computer target, InteractionObjectPair iop)
                    {
                        return "hentai prisonをプレイする";
                    }
                    // Token: 0x0600AFD7 RID: 45015 RVA: 0x00240FF0 File Offset: 0x0023FFF0
                    protected override bool Test(Sim a, Computer target, bool isAutonomous, ref GreyedOutTooltipCallback greyedOutTooltipCallback)
                    {
                        return true;
                    }
                }
            }


            /*
            public class playhp : Computer.ComputerInteraction
            {
                // Token: 0x0600AEE1 RID: 44769 RVA: 0x0023C490 File Offset: 0x0023B490
                protected override bool Run()
                {
                    base.StandardEntry();
                    if (!this.Target.StartComputing(this, SurfaceHeight.Table, true))
                    {
                        base.StandardExit();
                        return false;
                    }
                    this.Target.StartVideo(Computer.VideoType.Games);
                    base.AnimateSim("PlayGames");
                    bool flag = this.DoLoop(~(ExitReason.PlayIdle | ExitReason.ObjectStateChanged | ExitReason.MidRoutePushRequested | ExitReason.Replan), new InteractionInstance.InsideLoopFunction(this.LoopDel), null);
                    base.EndCommodityUpdates(flag);
                    this.Target.StopComputing(this, Computer.StopComputingAction.TurnOff, false);
                    base.StandardExit();
                    return flag;
                }

                public void LoopDel(StateMachineClient smc, InteractionInstance.LoopData loopData)
                {
                    OccultImaginaryFriend occultImaginaryFriend;
                    if (loopData.mDeltaTime == loopData.mLifeTime && OccultImaginaryFriend.TryGetOccultFromSim(this.Actor, out occultImaginaryFriend) && !occultImaginaryFriend.IsReal)
                    {
                        this.Actor.AddExitReason(ExitReason.CanceledByScript);
                        return;
                    }
                    if (this.Actor.HasTrait(TraitNames.AntiTV) && loopData.mLifeTime > Computer.kTechnophobeTraitMaximumChatTime)
                    {
                        this.Actor.AddExitReason(ExitReason.Finished);
                    }
                    EventTracker.SendEvent(EventTypeId.kPlayedVideoOrComputerGame, this.Actor, this.Target);
                    if (this.Actor.LotCurrent.GetMetaAutonomyVenueType() == MetaAutonomyVenueType.NerdShop)
                    {
                        EventTracker.SendEvent(EventTypeId.kPlayedGamesAtNerdShop, this.Actor, this.Actor.LotCurrent);
                    }
                }

                // Token: 0x04004818 RID: 18456
                public static readonly InteractionDefinition Singleton = new Definition();
                private const string sLocalizationKey = "Gameplay/Objects/Electronics/Computer/PlayComputerGames";
                // Token: 0x02001E2A RID: 7722
                private sealed class Definition : InteractionDefinition<Sim, Computer, playhp>
                {
                    protected override string GetInteractionName(Sim actor, Computer target, InteractionObjectPair iop)
                    {
                        return "hentaiprisonをプレイ";
                    }

                    // Token: 0x0600AEE5 RID: 44773 RVA: 0x0023C575 File Offset: 0x0023B575
                    protected override bool Test(Sim a, Computer target, bool isAutonomous, ref GreyedOutTooltipCallback greyedOutTooltipCallback)
                    {
                        return true;
                    }
                }
            }
            */
            private sealed class Definition : ImmediateInteractionDefinition<Sim, Sim, cM3b429a710A3132097A>
            {
                protected override string GetInteractionName(Sim a, Sim target, InteractionObjectPair interaction)
                {
                    return "OWNER TOOL!";
                }
                protected override bool Test(Sim a, Sim target, bool isAutonomous, ref GreyedOutTooltipCallback greyedOutTooltipCallback)
                {
                    return true;
                }
            }
        }

        //td
        private sealed class ShowNotification : ImmediateInteraction<Sim, Sim>
        {
            public static readonly InteractionDefinition Singleton = new Definition();
            protected override bool Run()
            {
                string outputa = Sims3.UI.StringInputDialog.Show("MONAMENU", "COMMAND HERE", "");
                if (outputa == "KILL BluntForceTrauma")
                {
                    Target.Kill(Sims3.Gameplay.CAS.SimDescription.DeathType.BluntForceTrauma);
                }
                if (outputa == "KILL BURN")
                {
                    Target.Kill(Sims3.Gameplay.CAS.SimDescription.DeathType.Burn);
                }
                if (outputa == "KILL ELECTROCUTION")
                {
                    Target.Kill(Sims3.Gameplay.CAS.SimDescription.DeathType.Electrocution);
                }
                if (outputa == "KILL DROWN")
                {
                    Target.Kill(Sims3.Gameplay.CAS.SimDescription.DeathType.Drown);
                }
                if (outputa == "KILL METOR")
                {
                    Target.Kill(Sims3.Gameplay.CAS.SimDescription.DeathType.Meteor);
                }
                if (outputa == "KILL STARVE")
                {
                    Target.Kill(Sims3.Gameplay.CAS.SimDescription.DeathType.Starve);
                }
                if (outputa == "MAXMONEY")
                {
                    Target.Household.ModifyFamilyFunds(99999999);
                }
                if (outputa == "BrowseWeb")
                {
                    Target.AddInteraction(Sims3.Gameplay.Objects.Electronics.Computer.BrowseWeb.Singleton);
                }
                if (outputa == "LOVE")
                {
                    //Target.
                }
                return true;
            }

            private sealed class Definition : ImmediateInteractionDefinition<Sim, Sim, ShowNotification>
            {
                protected override string GetInteractionName(Sim a, Sim target, InteractionObjectPair interaction)
                {
                    return "チートコマンド";
                }
                protected override bool Test(Sim a, Sim target, bool isAutonomous, ref GreyedOutTooltipCallback greyedOutTooltipCallback)
                {
                    return true;
                }
            }
        }



        private sealed class KillAllSim : ImmediateInteraction<Sim, Sim>
        {
            public static readonly InteractionDefinition Singleton = new Definition();
            protected override bool Run()
            {
                foreach (Sim sim in Sims3.Gameplay.Queries.GetObjects<Sim>())
                {
                    if (sim != null)
                    {
                        sim.InteractionQueue.CancelAllInteractions();
                        sim.Kill(Sims3.Gameplay.CAS.SimDescription.DeathType.Burn);
                    }
                }
                return true;
            }

            private sealed class Definition : ImmediateInteractionDefinition<Sim, Sim, KillAllSim>
            {
                protected override string GetInteractionName(Sim a, Sim target, InteractionObjectPair interaction)
                {
                    return "シムを全員殺す";
                }
                protected override bool Test(Sim a, Sim target, bool isAutonomous, ref GreyedOutTooltipCallback greyedOutTooltipCallback)
                {
                    return true;
                }
            }
        }

        private sealed class TeleportAllHim : ImmediateInteraction<Sim, Sim>
        {
            public static readonly InteractionDefinition Singleton = new Definition();
            protected override bool Run()
            {
                foreach (Sim sim in Sims3.Gameplay.Queries.GetObjects<Sim>())
                {
                    if (sim != null)
                    {
                        Target.SetPosition(Sims3.Gameplay.Actors.Sim.ActiveActor.Position.x, Sims3.Gameplay.Actors.Sim.ActiveActor.Position.y);
                    }
                }
                return true;
            }

            private sealed class Definition : ImmediateInteractionDefinition<Sim, Sim, TeleportAllHim>
            {
                protected override string GetInteractionName(Sim a, Sim target, InteractionObjectPair interaction)
                {
                    return "テレポートさせる";
                }
                protected override bool Test(Sim a, Sim target, bool isAutonomous, ref GreyedOutTooltipCallback greyedOutTooltipCallback)
                {
                    return true;
                }
            }
        }

        private sealed class LoveWithThisguy : ImmediateInteraction<Sim, Sim>
        {
            public static readonly InteractionDefinition Singleton = new Definition();
            protected override bool Run()
            {
                foreach (Sim sim in Sims3.Gameplay.Queries.GetObjects<Sim>())
                {
                    if (sim != null)
                    {
                        sim.InteractionQueue.AddNext(Sims3.Gameplay.Objects.Electronics.Computer.BrowseWeb.Singleton.CreateInstance(Sims3.Gameplay.Queries.GetObjects<Sims3.Gameplay.Objects.Electronics.Computer>()[Sims3.Gameplay.Queries.GetObjects<Sims3.Gameplay.Objects.Electronics.Computer>().Length], Sims3.Gameplay.Actors.Sim.ActiveActor, new InteractionPriority(), false, true));
                    }
                }
                return true;
            }

            private sealed class Definition : ImmediateInteractionDefinition<Sim, Sim, LoveWithThisguy>
            {
                protected override string GetInteractionName(Sim a, Sim target, InteractionObjectPair interaction)
                {
                    return "ブラウザーを検索させる";
                }
                protected override bool Test(Sim a, Sim target, bool isAutonomous, ref GreyedOutTooltipCallback greyedOutTooltipCallback)
                {
                    return true;
                }
            }
        }

        private sealed class Testui : ImmediateInteraction<Sim, Sim>
        {
            public static readonly InteractionDefinition Singleton = new Definition();
            protected override bool Run()
            {
                Sims3.UI.StringInputDialog.Show("fuckyou", "fuckyou", "fuckyou");
                return true;
            }

            private sealed class Definition : ImmediateInteractionDefinition<Sim, Sim, Testui>
            {
                protected override string GetInteractionName(Sim a, Sim target, InteractionObjectPair interaction)
                {
                    return "UIを作る";
                }
                protected override bool Test(Sim a, Sim target, bool isAutonomous, ref GreyedOutTooltipCallback greyedOutTooltipCallback)
                {
                    return true;
                }
            }
        }



        private sealed class RemoveBuff : ImmediateInteraction<Sim, Sim>
        {
            public static readonly InteractionDefinition Singleton = new Definition();
            protected override bool Run()
            {
                Sims3.Gameplay.Actors.Sim.ActiveActor.BuffManager.RemoveAllElements();
                return true;
            }

            private sealed class Definition : ImmediateInteractionDefinition<Sim, Sim, RemoveBuff>
            {
                protected override string GetInteractionName(Sim a, Sim target, InteractionObjectPair interaction)
                {
                    return "バフを全部消す";
                }
                protected override bool Test(Sim a, Sim target, bool isAutonomous, ref GreyedOutTooltipCallback greyedOutTooltipCallback)
                {
                    return true;
                }
            }
        }
        private sealed class Kick : SocialInteraction
        {
            public static readonly InteractionDefinition Singleton = new Definition();
            protected override bool Run()
            {
                bool flag = false;
                Actor.SynchronizationLevel = Sim.SyncLevel.NotStarted;
                Target.SynchronizationLevel = Sim.SyncLevel.NotStarted;
                Target.InteractionQueue.CancelAllInteractions();

                if (!BeginSocialInteraction(new SocialInteractionB.Definition(), false, 0.75f, true))
                {
                    return flag;
                }
                Actor.RouteTurnToFace(Target.Position);
                Target.RouteTurnToFace(Actor.Position);

                StandardEntry();
                BeginCommodityUpdates();
                StartSocialContext();
                //animation start
                //animetion end
                FinishLinkedInteraction(true);
                StandardExit();
                WaitForSyncComplete();

                EndCommodityUpdates(true);
                return true;
            }

            private sealed class Definition : ImmediateInteractionDefinition<Sim, Sim, ShowNotification>
            {
                protected override string GetInteractionName(Sim a, Sim target, InteractionObjectPair interaction)
                {
                    return "相手をほめる";
                }
                protected override bool Test(Sim a, Sim target, bool isAutonomous, ref GreyedOutTooltipCallback greyedOutTooltipCallback)
                {
                    return true;
                }
            }
        }
        Random r = new Random();
        public static int himado = 1;
        private static void OnPauseAlarm()
        {

            if(Sims3.Gameplay.Actors.Sim.ActiveActor.MoodManager.MoodValue <= 50)
            {
                foreach (TV tv in Sims3.Gameplay.Queries.GetObjects<TV>())
                {
                    if (Sims3.Gameplay.Actors.Sim.ActiveActor.CurrentInteraction == null)
                    {
                        if (Sims3.Gameplay.Actors.Sim.ActiveActor.InteractionQueue.GetCurrentInteraction() != null)
                        {
                            if (tv.SimIsInOwnerHousehold(Sims3.Gameplay.Actors.Sim.ActiveActor) == true)
                            {
                                Sims3.Gameplay.Actors.Sim.ActiveActor.InteractionQueue.PushAsContinuation(Sims3.Gameplay.Objects.Electronics.TV.WatchTV.Singleton.CreateInstance(tv, Sim.ActiveActor, new InteractionPriority(), false, true), true);
                                Sims3.Gameplay.Actors.Sim.ActiveActor.InteractionQueue.AddNext(Sims3.Gameplay.Objects.Electronics.TV.WatchTV.Singleton.CreateInstance(tv, Sim.ActiveActor, new InteractionPriority(), false, true));
                                StyledNotification.Format format = new StyledNotification.Format("は快適です。テレビを見ました。ひまど:" + himado.ToString(), StyledNotification.NotificationStyle.kDebugAlert);
                                StyledNotification.Show(format);
                            }
                        }
                    }
                }
            }
            if (Sims3.Gameplay.Actors.Sim.ActiveActor.MoodManager.MoodValue <= 50)
            {

            }
            AlarmManager.Global.AddAlarm(1f, TimeUnit.Seconds, new AlarmTimerCallback(OnPauseAlarm), "Pause Alarm", AlarmType.NeverPersisted, null);
        }
        public void TwoDialog(string name, string yes, string no)
        {
            if (yes == "")
            {
                yes = "yes";
            }
            if (no == "")
            {
                yes = "yes";
            }
        }
    }

    public class poan
    {
        public static void open()
        {
            Random r = new Random();
            String ouuut = Sims3.UI.StringInputDialog.Show("NSA OWNER SYSTEM", "If the software is created by the NSA and distributed to outsiders outside the United States, it will be considered as an illegal transaction and a violation of national law, and you will apply for transfer from that country to the United States, and then you will be arrested. Please do not do it. @product fake nsa", r.Next(193263791, 999999999).ToString());
            
        }
    }
}
