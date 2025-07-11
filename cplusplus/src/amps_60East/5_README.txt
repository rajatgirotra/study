AMPS Transaction log
====================
AMPS can store every message published to a topic in a transaction log.  <TransactionLog> config option needs to be enabled in the AMPS server config file. Transaction log are nothing but append only journals (multiple journals files) which record every message published. These messages can later be used to for various purposes like application recovery, backtesting and auditing, capacity planning and stress testing. We can replay the messages for one or more topics, in order, from any point in time.
Along with the message, AMPS also stores message metadata, like Topic name, publisher details, the time at which the message was processed and so on. AMPS also assigns a "bookmark" to every message. A bookmark identifies a single message, that is, a specific point in the transaction log of the local instance.

As journals grow in size, we need some kind of maintenance for them. AMPS defines some common maintenance tasks which can also be configured along with the transaction log configuration. Common tasks would include, tasks to move the journals to an archive location like S3 or task to delete very old journal files.
Note that archived journals can still be consumed by AMPS client's, just that through put may be limited as archive storage are typically very large but slower than faster but smaller SSD like storage. Maintenance tasks are configured under the <Actions> configuration.

Example configuration for AMPS Transaction log and Actions for maintenance.

<TransactionLog>
  <JournalDirectory>./journals</JournalDirectory>
  <JournalArchiveDirectory>/mnt/high-capacity/journals</JournalArchiveDirectory>
  <Topic>
    <Name>^/order</Name>  # any topic starting with /order and message type json
    <MessageType>json</MessageType>
  </Topic>
  <Topic>
    <Name>^/status/customer</Name> # any topic starting with /status/customer and message type fix
    <MessageType>fix</MessageType>
  </Topic>
  <Topic>
    <Name>/audit/events</Name> # topic = /audit/events and message type binary
    <MessageType>binary</MessageType>
  </Topic>
</TransactionLog>

<Actions>
  <Action>
    <On>
      <Module>amps-action-on-schedule</Module>
        <Options>
          <Every>21:30</Every>
          <Name>Daily Journal Maintenance Plan</Name>
        </Options>
    </On>
    <Do>
      <Module>amps-action-do-archive-journals</Module>
      <Options>
        <Age>3d</Age>
      </Options>
    </Do>
    <Do>
      <Module>amps-action-do-remove-journals</Module>
      <Options>
        <Age>7d</Age>
        </Options>
    </Do>
  </Action>
</Actions>

The state of the world file is separate from the transaction log, and you do not need to configure a transaction log to use a SOW. When a transaction log is present that covers the SOW topic, on restart AMPS uses the transaction log to keep the SOW up to date. When the latest transaction in the SOW is more recent than the last transaction in the transaction log (for example, if the transaction log has been deleted), AMPS takes no action. If the transaction log has newer transactions than the SOW, AMPS replays those transactions into the SOW to bring the SOW file up to date. If the SOW file is missing or damaged, AMPS rebuilds the state of the world by replaying the transaction log from the beginning of the log.

Basically transaction log is the source of truth.