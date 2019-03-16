﻿using System;
using ClashRoyale.Logic;
using ClashRoyale.Protocol.Messages.Server;
using DotNetty.Buffers;

namespace ClashRoyale.Protocol.Messages.Client
{
    public class VisitHomeMessage : PiranhaMessage
    {
        public VisitHomeMessage(Device device, IByteBuffer buffer) : base(device, buffer)
        {
            Id = 14113;
        }

        public long UserId { get; set; }

        public override void Decode()
        {
            UserId = Buffer.ReadLong();
        }

        public override async void Process()
        {
            Console.WriteLine(UserId);
            await new VisitedHomeDataMessage(Device)
            {
                UserId = UserId
            }.Send();
        }
    }
}